#include "StdAfx.h"
#include "TextRenderer.h"
#include "Point4.h"

void TextRenderer::DrawText(const char *text, float x, float y, float sx, float sy, bool bold) const
{
  auto face = bold ? italic_face : normal_face;

  const char *p;
  auto g = face->glyph;

  /* Create a texture that will be used to hold one "glyph" */
  GLuint tex;

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(uniform_tex, 0);

  /* We require 1 byte alignment when uploading texture data */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /* Clamping to edges is important to prevent artifacts when scaling */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  /* Linear filtering usually looks best for text */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  /* Set up the VBO for our vertex data */
  glEnableVertexAttribArray(attribute_coord);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

  /* Loop through all characters */
  for (p = text; *p; p++) 
  {
    /* Try to load and render the character */
    if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
      continue;

    /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows,
      0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

    /* Calculate the vertex and texture coordinates */
    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w = g->bitmap.width * sx;
    float h = g->bitmap.rows * sy;

    Point4 box[4] = {
      { x2, -y2, 0, 0 },
      { x2 + w, -y2, 1, 0 },
      { x2, -y2 - h, 0, 1 },
      { x2 + w, -y2 - h, 1, 1 },
    };

    /* Draw the character on the screen */
    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    /* Advance the cursor to the start of the next character */
    x += (g->advance.x >> 6) * sx;
    y += (g->advance.y >> 6) * sy;
  }

  glDisableVertexAttribArray(attribute_coord);
  glDeleteTextures(1, &tex);
}

void TextRenderer::Initialize()
{
  if (FT_Init_FreeType(&library))
  {
    std::cerr << "could not init freetype" << std::endl;
    return;
  }

  // this is not even remotely portable
  auto location = "FreeMono.ttf";
  if (FT_New_Face(library, location, 0, &normal_face))
  {
    std::cerr << "could not make font from " << location << std::endl;
    return;
  }

  FT_Select_Charmap(normal_face, FT_ENCODING_MS_SYMBOL);

  // here comes the font size
  char_width = 10;
  char_height = 14;
  FT_Set_Pixel_Sizes(normal_face, char_width, char_height);

  // start bold text
  auto location2 = "FreeMono.ttf";
  if (FT_New_Face(library, location2, 0, &italic_face))
  {
    std::cerr << "could not make font from " << location2 << std::endl;
    return;
  }
  FT_Select_Charmap(italic_face, FT_ENCODING_MS_SYMBOL);
  FT_Set_Pixel_Sizes(italic_face, char_width, char_height);
  // end bold text

  program = create_program("text.v.glsl", "text.f.glsl");
  if (program == 0)
  {
    std::cerr << "failed to load shaders" << std::endl;
    return;
  }

  // amazing. now...
  attribute_coord = get_attrib(program, "coord");
  uniform_tex = get_uniform(program, "tex");
  uniform_color = get_uniform(program, "color");

  if (attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
  {
    std::cerr << "failed to get something " << std::endl;
    return;
  }

  // create the vertex buffer object
  glGenBuffers(1, &vbo);
}
