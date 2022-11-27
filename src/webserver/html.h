#include <string>

class WiFiServer {
  

};


class TemplateHtml {
private:
  int button_num;
  std::string** suffices;
  std::string** texts;
public:
  TemplateHtml(int _button_num, std::string** _suffices, std::string** _texts):button_num(_button_num), suffices(_suffices), texts(_texts) {
  }
  

  void handle_buttons();

};