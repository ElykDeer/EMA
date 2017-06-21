//Can paint in various colors on linux
/* Short Color Reference:
 * -30 - Normal
 * -25 - Blink
 * 1 - Red
 * 2 - Green
 * 3 - Yellow
 * 4 - Blue
 */
#ifdef _WIN32
  void startPaint(const int color) {}
  void endPaint() {}
  string commandPrompt = "\ncommand: ";
#else
  void startPaint(const int color)
  {
    cout << "\033[" << color+30 << "m";
  }
  void endPaint()
  {
    cout << "\033[0m";
  }
  string commandPrompt = "\033[32m\ncompile: \033[0m";
#endif
