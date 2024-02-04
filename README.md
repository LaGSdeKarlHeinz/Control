# Concept network 

fonctionnement server - client, avec des socket 

2 niveaux de routages des données : 
1er niveau
premièrement on reçois des infos par radio  tranmise au serveur, chaque data est labellé d'une manière unique. Les différente interface peuvent s'abonner à des donnée en faisant une requête. Lorsque qu'une données reçu par le serveur de la radio esr reçu elle regarde pour chacun des clients si il a des données auxquel il était abonnée. Si c'est le cas, les données sont transmisent en Json.

2ème niveau:
les données reçu doivent être update les bons champs sur l'UI, avec le ClientManager, lorsqu'un panneau est crée il peut s'abonner a certains champs de données et passe une callback qui est un setter pour ce champ de données