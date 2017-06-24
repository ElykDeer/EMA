#ifndef SIM_ENTICAP
#define SIM_ENTICAP 1

//Wrapper for an entity..adds
    //a "unique identifier"
    //a pointer to its hex
  class Enticap
  {
  public:
      Enticap(Entity* const newEntity, Hex* hexP);

      Hex* getHexP() const;

      ~Enticap(); //be careful with this fellow... Changing how it works could
                  //be really really bad (memory leaks)

      //Entity* UID() const;

      //std::size_t TUID() const;

  private:
      Entity* const entityP;
      Hex* hexP;
  };

  #endif
