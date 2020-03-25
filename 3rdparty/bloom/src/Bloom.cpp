#include "StdAfx.h"
#include "Window.h"
#include "TextBuffer.h"

using namespace std;

int main(int ac, char* av[])
{
  // create a single window and show it
  Window window("Test", 1280, 720);

  // let's try to create a viewport + buffer
  auto buffer = make_shared<TextBuffer>(40, 40);
  buffer->add_string("One", false);
  buffer->add_string(string("Two"), false);
  buffer->add_string(string("Three"), false);
  buffer->add_string(string("Four"), false);
  buffer->add_string(string("Five"), false);
  window.buffers.push_back(buffer);
  auto viewport = make_shared<Viewport>(buffer);
  window.viewports.emplace_back(viewport);

  auto viewport2 = make_shared<Viewport>(buffer, Size{ 40,40 }, Point{}, Point{ 45, 0 });
  window.viewports.emplace_back(viewport2);

  auto viewport3 = make_shared<Viewport>(buffer, Size{ 40,40 }, Point{}, Point{ 90, 0 });
  window.viewports.emplace_back(viewport3);

  window.Show();

  return 0;
}
