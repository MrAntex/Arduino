#include <Servo.h> // Ca c'est la librairie pour pouvoir utiliser un servomoteur,pas besoin si tu en utilise pas
 
// Init de toutes les variables que tu dois modifier en fonction de tes besoins :
const float g = 9.81; // LE POINT G LOL
float k = ?.??; // Ca c'est ton bordel, tu les initialise comme tu veux
float lo = ?.??; // idem, chacun sa merde
const float pres = 0.??; //la précision de ta balance (en V/kg)
const float masse_vide = ?.??; //Ca c'est ta masse à vide de ton bordel, pour la soustraire à la masse totale
const float long_max = ?.??; // Içi tu mets la longueur maximale de ton vérin/ressort une fois étiré/rétracté


// HEY léger point sur les float, tu as remarqué que j'ai mis des '?.??' en valeur, et pas des '?' ou des '??' ou même des '???' ou même des '? ?' ou même des '¿¿'. Non j'ai mis '?.??' parce que c'est comme ça qu'on utilise des float, si tu veux mettre 2, tu mets 2.00, etc. Sinon le compilateur t'arrache la gueule (et mon prof de prog aussi) donc oublies pas si tu dois faire marcher ton prog


float m_tot, m, l, dist_ret, degre; //Ici tu touches pas, j'initialise juste les variables pour que le prog sache que c'est des nombres flottants (cf l'autre prog tmtc)
//
// * const pinBouton = 2; // GO A LA FIN POUR SAVOIR A QUOI SERVENT LES
// * int launch = 0;      // COMMENTAIRES AVEC UNE *
// Globalement on dit que le pin auquel est relié le bouton est le pin 2
// Et que au début le bouton n'est pas activé en initialisant une nouvelle
// variable launch de type int (qui n'est pas vraiment un int mais nsm) et
// qui prendra par la suite l'état du bouton
//
//
// Pour toute la suite je considère que ton système fonctionne avec un
// servomoteur, dans l'absolu tu utilises ce que tu veux, l'avantage du
// servo c'est que il y a peu de souçi mécanique ou de fuite comme tu peux
// avoir avec un vérin et c'est vachement plus précis komememe
//

Servo myservo; // Donc on crée une instance de la classe Servo, en gros tu crée une """"variable"""" de ""type"" Servo, tu me dis si tu veux plus de détails mais je pense pas que ce soit super utile pour ton truc

void setup() { // paramétrage/initialisation du programme, parce qu'il faut bien commencer un jour
serial begin(9600); // Comme le dernier prog, ça sert surtout pour la sortie console, idem, check l'autre prog si t'a besoin mais sinon tu peux enlever la ligne jpense

myservo.attach(9); // tu paramètre ton servo en lui disant qu'il est branché sur le pin 9 de ta carte, tu le modifie en fonction


}

void loop() { // début du vrai prog, el famoso void loop

m_tot = analogRead(A0) * (5.0 / 1023.0) / pres; // Similaire à l'autre prog, tu prend la valeur que tu lis sur l'entrée A0 (ou tu as bien évidemment branché ta balance), je précise que JE NE SAIS PAS comment marchent ces merdes sous arduino ok ? genre moi je t'ai mis ça comme un sagouin, je suis quasi sur qu'il en existe qui marchent comme ça mais peut-être (surement) pas celles dont vous auriez besoin pour peser des vraies personnes ptdr. Mais sur le principe ça marchera tkt.
// Donc idem que sur l'autre prog, le CAN, lecture des bits, plage de valeurs sur 5v, toussa toussa
// Ah oui et je divise par la précision de ta balance que tu as initialisée au début

m = m_tot - masse_vide; // m c'est la masse du sac de viande que tu pose sur ta balance, tu devrais être capable de déduire l'explication de ce calcul tout seul, inchallah

// * launch = digitalRead(pinBouton); // On check l'état du bouton et on stocke cet état dans launch (HIGH = appuyé, LOW = relaché)

	if(m>1.0 /* * && launch == HIGH */){ // La je fais un test pour que ton servo il se retracte que si il y a plus d'1kg sur la balance, pour éviter les erreurs principalement et les décalages à force d'utilisation

		retract_ress(m); // on appelle la procédure dédiée au ressort. Oui UNE PROCEDURE WOW OMG AMAZING CE SCALE UP DE DINGUE LE PROGRAMME PIQUE AU STEROIDES !!!§!!
// Bref sinon en vrai on appelle la procédure pour faire bouger le ressort avec la masse mesurée en paramètre, + d'explications sur la proc plus bas msieur
	}
//Pas obligé mais okazou, on remet le servomoteur (donc le ressort) à sa position initiale (0°) si le poids est de moins de 1kg ou si le bouton est relaché. En soit la proc le fait déja, mais à force de se faire enculer par des exceptions débiles en codant, jsuis devenu parano
	else{ // sinon, t'es pas débile non plus
		servo.write(0); // on remet le servo à 0°
	} 

}// Fin du void loop


void retract_ress(float read){ // LA PROCEDURE WOUHOU
// Ce qui va suivre c'est pour sucer un peu, tu peux passer si tu t'en tamponne l'oreille.
// Donc ça s'appelle une procédure parce que c'est une fonction qui retourne rien (d'ou le void au début, c'est le type de retour), ensuite on la nomme, en l'occurrence 'retract_ress', et après on lui mets des attributs, ses paramètres, en les typant, donc la un flottant qu'on appelle read, parce que c'est la valeur qu'on va lire. On aurait pu l'appeler m comme dans le loop ou trublion tu t'en ballec, faut juste savoir que c'est comme ça que tu y fera référence dans la suite de ta procédure, tu va comprendre. j'ai juste pas mis m pour par confondre les deux. 
// Faut savoir que (presque par définition) la procédure est en dehors du void loop, donc contrairement à elle, elle ne va pas s'éxecuter en boucle. Malinx le lynx
// Fin du suçage, éssuie toi bien au bord des levres

l = sqrt((read*g)/k)+lo; // Ca c'est ta formule, je crois que le 'sqrt()' juste comme ça il marche pas, il me semble qu'il faut une librairie de maths ou un truc du genre, dis moi si tu veux que je creuse le sujey

dist_ret = 1-l; // Encore une fois c'est ton gloubiboulga

degre = dist_ret / long_max * 180; // La c'est l'application sur le fonctionnement avec un servo, mais t'es pas obligé hein je le rappelle. Mais ducoup pour expliquer c'est tout con, en imaginant que en faisant 180° ton servo étire à fond ton ressort, alors on calcule de combien de ° il doit tourner pour aller à la distance voulue. C'est peut-être la merde avec ton truc du 1-l j'ai pas tout compris parce que ducoup si l>1 ca fait un angle négatif et ça il va pas kiffer le servo ^^'
// Je suis quasi certain que tu as compris le principe, donc je pense que tu sera capable de modifier ça si ça colle pas exactement avec ce qu'il fallait, message si besoin

servo.write(degre); // On dit enfin a ce putain de servo de bouger sa daronne du nombre de degré voulu

delay(500); // On attend une demie seconde okazou pour être sur que le ressort est bien étiré, on peut modifier le délai, on peut même l'enlever en théorie parce que normalement le servo ne rend pas la main au prog avant d'avoir terminé son mvt, menfin, ça mange padpain

declencher_ress(); // La tu imagine que ça lance ta procédure de lâché de ressort, vu que je sais pas vraiment comment tu veux faire je t'ai juste mis ça pour dire que içi il faudra faire l'intégration du laché de ressort, du rammenage de piston, du réenclenchement global de ton canon à gens

servo.write(0); // Et on reset la position du servo, c'est pour ça que la vérification dans le void loop est vraiment la okazou

} // Fin de la proc




// Hey, donc les commentaires avec * il y en a 4 il me semble, c'est si tu voulais que le déclenchement de ton ressort se fasse via un bouton externe et pas juste quand un pelo fout son cul sur la balance. Pour utiliser ce truc enlève juste les // et /* */ des commentaires concernés ainsi que les * Ca fera que tu aura un bouton connecté au pin n°2 de ton arduino et que si il y a + d'1 kg sur ta balance et que tu appuie sur le bouton alors le ressort se rétracte, si tu laisse les commentaires ou si tu supprimes toutes les lignes ça fait que le ressort est tiré des que la balance >1 kg. Et si tu enlèves toutes les autres lignes aussi ça fait qu'il n'y a plus de programme et que j'ai fait tout ça pour rien, et donc par corrélation que tu peux allègrement aller baiser ta mère :)






// THIS IS THE END gl hf mon pote, hésite pas si t'as la moindre question ou si t'as besoin de quoi que ce soit. Passe le bonsoir à Lou et dis lui bien que je suis vraiment désolé d'avoir pris autant de temps :/
// (mais dis lui aussi que j'oublie pas qu'elle me doit une faveur hein)

// Débizou <3
