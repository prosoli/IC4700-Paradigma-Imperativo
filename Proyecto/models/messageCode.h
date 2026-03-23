#pragma once

//Este es un enum que se utiiiza para definir el codigo del comando que se le esta enviando al servidor, asi el servidor va a poder identificar que tipo de comando recibe y procesarlo de la forma correcto. A cada mensaje le asigno un codigo usando solo el nuemro.
enum MessageCode {
    ViewTables = 0,
    CreateOrder = 1,
    ViewOrders = 2,
    ModifyOrder = 3,
    ViewProducts = 4
};