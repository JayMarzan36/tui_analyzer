#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main() {
  int counter = 0;

  auto button = Button("Click me", [&] {
    counter++;
  });

  auto renderer = Renderer(button, [&] {
    return vbox({
      text("FTXUI demo") | bold | center,
      separator(),
      text("Counter: " + std::to_string(counter)) | center,
      separator(),
      button->Render() | center,
      text("Press q or Esc to quit") | dim | center,
    }) | border;
  });

  auto screen = ScreenInteractive::TerminalOutput();

  renderer = CatchEvent(renderer, [&](Event event) {
    if (event == Event::Character('q') || event == Event::Escape) {
      screen.Exit();
      return true;
    }
    return false;
  });

  screen.Loop(renderer);
  return 0;
}

