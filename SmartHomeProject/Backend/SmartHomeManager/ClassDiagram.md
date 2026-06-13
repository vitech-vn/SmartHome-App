                    Mobile App (QML)
                          |
                          |
                 Signal / Slot
                          |
                          ↓
              +----------------------+
              |  SmartHomeManager    |
              |  (Controller)        |
              +----------------------+
                 |        |        |
                 |        |        |
                 ↓        ↓        ↓

              Device   Energy   Alert
              Manager  Tracker  System

                 |
                 ↓

          +---------------+
          | Device (Base) |
          +---------------+
                 |
   -----------------------------------
   |        |       |       |        |
 Light    Fan      AC      TV     Fridge
   |
 WashingMachine
 WaterHeater
 Microwave
 RiceCooker
 Curtain


                 ↑

        SimulationEngine
