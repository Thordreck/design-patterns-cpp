cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(design_patterns_cpp VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(specification)
add_subdirectory(liskov_substitution)
add_subdirectory(interface_segregation)
add_subdirectory(dependency_inversion)
add_subdirectory(builder)
add_subdirectory(fluent_builder)
add_subdirectory(groovy_builder)
add_subdirectory(builder_facets)
add_subdirectory(factory_method)
add_subdirectory(factory_class)
add_subdirectory(inner_factory)
add_subdirectory(abstract_factory)
add_subdirectory(functional_factory)
add_subdirectory(prototype)
add_subdirectory(prototype_factory)
add_subdirectory(prototype_serialization)
add_subdirectory(singleton)
add_subdirectory(singleton_injection)
add_subdirectory(singleton_lifetime)
add_subdirectory(monostate)
add_subdirectory(multiton)
add_subdirectory(pimpl_idiom)
add_subdirectory(pimpl_shrink_wrapped)
add_subdirectory(bridge)
add_subdirectory(composite)
add_subdirectory(neural_networks)
add_subdirectory(array_backed_properties)
add_subdirectory(dynamic_decorator)
add_subdirectory(static_decorator)
add_subdirectory(functional_decorator)
add_subdirectory(facade)
add_subdirectory(flyweight_handmade)
add_subdirectory(flyweight_boost)
add_subdirectory(flyweight_text_formatting)
add_subdirectory(proxy_property)
add_subdirectory(proxy_virtual)
add_subdirectory(proxy_communication)
add_subdirectory(responsibility_chain_pointer)
add_subdirectory(responsibility_chain_broker)
add_subdirectory(command)
add_subdirectory(command_undo)
add_subdirectory(command_macro)
add_subdirectory(interpreter_handmade_lexing)
add_subdirectory(interpreter_handmade_parsing)
add_subdirectory(iterator_binary_tree)
add_subdirectory(iterator_facade)
add_subdirectory(mediator)
add_subdirectory(mediator_event_broker)
add_subdirectory(memento)
add_subdirectory(memento_undo_redo)
add_subdirectory(observer)
add_subdirectory(observer_boost)
add_subdirectory(observer_dependency_issues)
add_subdirectory(observer_thread_safety)
add_subdirectory(state_classic)
add_subdirectory(state_handmade)
add_subdirectory(state_boost)
add_subdirectory(strategy_dynamic)
add_subdirectory(strategy_static)
add_subdirectory(template_method)
add_subdirectory(visitor_intrusive)
add_subdirectory(visitor_reflective)
add_subdirectory(visitor_classic_double_dispatch)
add_subdirectory(visitor_acyclic)
add_subdirectory(visitor_multimethods)
add_subdirectory(visitor_variant)
