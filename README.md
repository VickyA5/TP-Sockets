# Sockets

Insertar un **DIAGRAMA AQUI**

Ejemplo:

![img](https://www.plantuml.com/plantuml/png/TP71QiCm38RlUWgHKqV96-nGs64CIYc4FO2gQAs94nTPoHYZxpxFhTScC1-CzCl-zClUH2EriVTmSgsWz6VxGZ9JTnXDubLbf-m50Cx47Hq5g_SeYc-3YNuGIuNu3O38dcB45-zaiAsmZKgfW6cjUtB3wYd55xWySFOQB73mcJ07t4f_QYCwYPOBOORPYNq6xMQK9d0dLlf76LhoFbj8gGfF9SsExgnNwgy3uQBr_nFDZltkhWqA6NjpXizrZSKxb22hoxTSLBCTW4todtxf1m00)


Codigo PlantUML que genero ese diagrama:

```
@startuml
hide empty attributes
hide circle


package "User Interface"  {

  class ClientLectura {
    +main()
  }
}

package "Protocol"  {
  class ClientProtoco
  class ServerProtocolo
}

package "Network"  {
  class Socket {
    +sendall()
    +recvall()
  }
}


package "Game"  {
 
  class ServerLectura {
    +main()
  }
 class ServerServidor

}


Network <-- Protocol
Protocol <-- "User Interface"
Protocol <-- "Game"

@enduml
```

Utilicé el respositorio ofrecido por la cátedra para los sockets.