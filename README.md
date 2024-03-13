# Sockets

Insertar un **DIAGRAMA AQUI**

Ejemplo:

![img](http://www.plantuml.com/plantuml/png/RL71JiCm3BtxAvvs0i5-076On05nGKm8RQkuXDJRGjDuIjmXXFhlf1qjg-2KPpj-zdjU93LHczhJtfKChW_w2QCQtLkZd4vPwwBrJ4G7OokpOynU4aSy1EMuDPPdm1S1rfkKK1J5YE-yuw1z4RYgZGiNbnctr9vnFKLHiU8dBElrUiIRpMRIyCZw8R6Q_7yMM_4uAN4eZVVzi1n6jiSXR6diMIwNr9whkZVrLCjgjVgTmF78yNyjGPGHtMwla6stEsxoHbxG1F1xDjNBDQoKRA1IclGQCcNFo_cHMk05WIqdrvbEe1-Dk9tFCHX40-YoVsumhPwq42so4_cwtm00)


Codigo PlantUML que genero ese diagrama:

```
@startuml
hide empty attributes
hide circle


package "User Interface"  {
  class ZZZ
  class Client {
    +main()
  }
}

package "Protocol"  {
  class XXX
  class YYY
}

package "Network"  {
  class Socket {
    +sendall()
    +recvall()
  }

  class QQQ
}


package "Game"  {
  class WWW
  class Server {
    +main()
  }
}

note right of XXX : Solo un ejemplo, codea todas\nlas clases como lo necesites


Network <-- Protocol
Protocol <-- "User Interface"
Protocol <-- "Game"

@enduml
```
