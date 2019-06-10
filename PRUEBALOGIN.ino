//CAMBIAR RED Y CLAVE DE RED
//USUARIO= Usuario; CONTRASEÑA= Usuario 

#include <ESP8266WiFi.h>                    
#include <ESP8266WebServer.h>

String ssid = "RED";
String contra = "CONTRASEÑA";

ESP8266WebServer server(80);

void Principal();
void Login();
void Error();


String usuario = "Usuario";
String pass = "Usuario";


void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, contra);

  Serial.print("\nCONECTANDO");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nConectado a red: ");
  Serial.println(WiFi.SSID());
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, Principal);
  server.on("/entrar", HTTP_POST, Login);
  server.onNotFound(Error);

  server.begin();
  Serial.println("\nEL SERVIDOR HA INICIADO");
}

void loop()
{
  server.handleClient();
}

void Principal()
{
  String html ="<!DOCTYPE html> <html lang=\"es\"> <head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"> <title>INGRESO</title> </head> <style> * { margin: 0; padding: 0; box-sizing: border-box; } body { background: rgb(50, 50, 50); } .contenedor { margin: 0 auto; width: 90%; } .formulario { background: #AF0F0F; margin: 0 auto; width: 40%; padding: 20px; border-radius: 10px; } .formulario form h2 { color: #FFF; text-align: center; } .formulario form .seccion { display: flex; justify-content: space-between; align-items: center; text-align: center; padding: 30px; } .formulario form .seccion .campo { color: #FFF; width: 49%; } .formulario form .seccion .campo label{ display: block; } .formulario form .seccion .campo .texto { margin: 5px 0; padding: 3px 7px; border-radius: 5px; } .acceder{ display: none; } .btn-acceso{ background: #FFF; padding: 10px 20px; color: #AF0F0F; cursor: pointer; transition: all ease .4s; border-radius: 5px; } .btn-acceso:hover{ color: #FFF; background: rgb(65, 6, 6); } .acceso{ width: 100%; text-align: center; margin-bottom: 20px; } ";
  html +="@media (max-width: 1200px){ .formulario{ width: 60%; } } ";
  html +="@media (max-width: 800px){ .formulario{ width: 80%; } } ";
  html +="@media (max-width: 600px){ .formulario{ width: 90%; } .formulario form .seccion { display: flex; flex-direction: column; } .formulario form .seccion .campo { color: #FFF; width: 100%; } } ";
  html +="@media (max-width: 350px){ .formulario{ width: 95%; } .formulario form { padding: 0; } .formulario form .seccion { padding: 10px 0; } .formulario form .seccion .campo .texto { margin: 2px 0; padding: 0px 0px; border-radius: 0px; } } </style> <body> <div class=\"contenedor\"> <div class=\"formulario\"> <form action=\"/entrar\" method=\"POST\"> <h2>INGRESO</h2> <hr> <section class = \"seccion\"> <div class=\"campo\"> <label for=\"usuario\">Nombre de usuario:</label> <input class = \"texto\" type=\"text\" name=\"usuario\" id = \"usuario\" maxlength=\"20\" placeholder=\"Usuario\"> </div> <div class=\"campo\"> <label for=\"password\">Contraseña:</label> <input placeholder = \"Contraseña\" type=\"password\" class = \"texto\" id = \"password\" name=\"password\"> </div> </section> <section class=\"acceso\"> <input type=\"submit\" value=\"Acceder\" class=\"acceder\" id=\"acceder\" name=\"acceder\"> <label for=\"acceder\" class = \"btn-acceso\">ACCEDER</label> </section> </form> </div> </div> </body> </html>";

   server.send(200, "text/html", html);
}

void Login()
{
  if(!server.hasArg("usuario") || !server.hasArg("password") || server.arg("usuario") == NULL || server.arg("password") == NULL)
  {
    server.send(400, "text/plain", "COMPLETE EL ACCESO");
    return;
  }
  if(server.arg("usuario") == usuario && server.arg("password") == pass)
  {
    String html ="<!DOCTYPE html> <html lang=\"es\"> <head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"> <link rel=\"stylesheet\" href=\"CSS/Estilos.css\"> <title>Portal de Configuracion</title> <meta name=Description content=\"Muestra los tipos de enlaces que podemos usar\" /> <meta http-equiv=Content-Language content=es/> <meta name=distribution content=global/> <meta name=\"Robots\" content=\"all\"/> </head> <style> * { margin: 0; padding: 0; box-sizing: border-box; } .contenedor { overflow: hidden; width: 90%; margin: 0 auto; } .contenedor .titulo { color: #AF0F0F; width: 100%; text-align: center; border-bottom: 1px solid #000; line-height: 0.1em; margin-top: 30px; } .contenedor .titulo span { background: #fff; padding: 0 10px; } .contenedor .formulario { overflow: hidden; margin: 0 auto; display: flex; justify-content: center; padding: 30px; width: 70%; border: 3px double #AF0F0F; margin-top: 30px; } .contenedor .formulario form { width: 50%; } .contenedor .formulario form .seccion { padding: 10px 0; } .contenedor .formulario form .seccion hr { margin-bottom: 10px; color: #AF0F0F; } .contenedor .formulario form .seccion .campo { display: flex; align-items: center; justify-content: space-between; } .contenedor .formulario form .seccion .campo .texto { margin: 5px 0; padding: 3px 7px; } .contenedor .formulario form .botones { margin-top: 15px; display: flex; justify-content: space-around; } .contenedor .formulario form .botones input { display: none; } .contenedor .formulario form .botones + label { background: #AF0F0F; padding: 10px 20px; color: #FFF; cursor: pointer; transition: all ease 0.4s; } .contenedor .formulario form .botones + label:hover { background: #490606; } ";
    html +="@media (max-width: 950px) { .contenedor { width: 100%; } .contenedor .titulo { color: #AF0F0F; width: 100%; border-bottom: none; } .contenedor .formulario { width: 90%; } } ";
    html +="@media (max-width: 650px) { .contenedor .titulo { text-align: left; } .contenedor .formulario { margin-top: 0px; border: none; width: 100%; } .contenedor .formulario form { width: 80%; } .contenedor .formulario form .seccion h2 { text-align: center; } .contenedor .formulario form .seccion .campo { padding: 5px 10px; } } ";
    html +="@media (max-width: 415px) { h2{ font-size: 20px; } body{ font-size: 11px; } .contenedor { width: 100%; } .contenedor .formulario form { width: 100%; } } </style> <body> <div class=\"contenedor\"> <h1 class=\"titulo\"><span>CONFIGURACIÓN</span></h1> <div class=\"formulario\"> <form action=\"Comprobar.php\" method = \"POST\"> <section class = \"seccion\"> <h2>Configuracion de AP</h2> <hr> <div class=\"campo\"> <label for=\"ssid_ap\">SSID:</label> <input class = \"texto\" type=\"text\" name=\"ssid_ap\" id = \"ssid_ap\" maxlength=\"20\" placeholder=\"SSID_AP\"> </div> <div class=\"campo\"> <label for=\"password_ap\">Password:</label> <input placeholder = \"Password\" type=\"password\" class = \"texto\" id = \"password_ap\" name=\"password_ap\"> </div> </section> <section class = \"seccion\"> <h2>Configuracion de WiFi</h2> <hr> <div class=\"campo\"> <label for=\"ssid_wifi\">SSID:</label> <input class = \"texto\" type=\"text\" name=\"ssid_wifi\" id = \"ssid_wifi\" maxlength=\"20\" placeholder=\"SSID_WiFi\"> </div> <div class=\"campo\"> <label for=\"password_wifi\">Password:</label> <input placeholder = \"Password\" class = \"texto\" type=\"password\" id = \"password_wifi\" name=\"password_wifi\"> </div> </section> <section class = \"seccion\"> <h2>Configuracion de MQTT</h2> <hr> <div class=\"campo\"> <label for=\"mqtt_server\">MQTT Server:</label> <input class = \"texto\" type=\"text\" name=\"mqtt_server\" id = \"mqtt_server\" maxlength=\"20\" placeholder=\"Servidor MQTT\"> </div> <div class=\"campo\"> <label for=\"id_client\">ID Cliente:</label> <input class = \"texto\" type=\"text\" id = \"id_client\" name=\"id_client\" placeholder = \"esp8266_01\"> </div> <div class=\"campo\"> <label for=\"topic_sub_01\">Topic Sub:</label> <input class = \"texto\" type=\"text\" id = \"topic_sub_01\" name=\"topic_sub_01\" placeholder = \"topic_sub\"> </div> <div class=\"campo\"> <label for=\"topic_pub_01\">Topic Pub:</label> <input class = \"texto\" type=\"text\" id = \"topic_pub_01\" name=\"topic_pub_01\" placeholder = \"topic_pub\"> </div> </section> <div class=\"botones\"> <input type=\"submit\" name = \"aplicar\" id = \"aplicar\" class=\"botones\"> <label for=\"aplicar\">Aplicar</label> <input type=\"Reset\" name = \"resetear\" id = \"resetear\" class=\"botones\"> <label for=\"resetear\">Resetear</label> </div> </form> </div> </div> </body> </html>";

    server.send(200, "text/html", html);
  }else
  {
    server.send(401, "text/plain", "ACCESO NO AUTORIZADO");
  }
}

void Error()
{
  server.send(404, "text/plain", "PAGINA NO ENCONTRADA");
}
