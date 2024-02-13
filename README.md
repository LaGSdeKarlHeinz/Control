# Concept network 

fonctionnement server - client, avec des socket 

2 niveaux de routages des données : 
1er niveau
premièrement on reçois des infos par radio  tranmise au serveur, chaque data est labellé d'une manière unique. Les différente interface peuvent s'abonner à des donnée en faisant une requête. Lorsque qu'une données reçu par le serveur de la radio esr reçu elle regarde pour chacun des clients si il a des données auxquel il était abonnée. Si c'est le cas, les données sont transmisent en Json.

2ème niveau:
les données reçu doivent être update les bons champs sur l'UI, avec le ClientManager, lorsqu'un panneau est crée il peut s'abonner a certains champs de données et passe une callback qui est un setter pour ce champ de données

# FirehornGUI 

inspi design : https://www.google.com/search?sca_esv=2610265ff35e352d&sxsrf=ACQVn0_TsTecfndTSljVxfyZIotZF1ggsQ:1707342823399&q=modern+ui&tbm=isch&source=lnms&prmd=ivsnbmtz&sa=X&ved=2ahUKEwiMiv7Tm5qEAxWv9gIHHWovDWUQ0pQJegQIEhAB&biw=2560&bih=1279&dpr=1#imgrc=0YlyaGQ0j6tJfM

note pour les requête : 
get :                                        
    getSerialStatus => response = "serialNameUsed", "serialStatus" (fields expected)


when adding stuff to res make sure to compile the qrc with the following command : 

```rcc -binary resources.qrc -o resources.rcc```


# Installation 

QTSvg : sudo apt-get -y install libqt6svg6-dev

Rcc command : fedora : sudo dnf install qt-devel

SerialPort : ubuntun : sudo apt-get install libqt5serialport5-dev

# Communication structure 

```
communication from client to server :
{
    header: post | get | internal,
    payload: {
        source : <client-ip>,
        args*...
    }
}

communication from sever to client :
{
    header: post | get | internal,
    payload: {
        source : GSE | AV,
        args*...
    }
}
```
get :                                        
    getSerialStatus => response = "serialNameUsed", "serialStatus" (fields expected)