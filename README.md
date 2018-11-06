# CityProjectGIG
Génération de villes en 3D (Modélisation Géométrique)

Note : Ce README est en cours de rédaction, il peut ne pas être tout à fait complet.

Dans un souci de réalisme dans le développement de nos villes en 3D, nous avons décidé de fragmenter la surface de notre ville en plusieurs zones, représentant en quelque sorte les quartiers.

Nous nommerons ces zones ainsi : centre-ville, périphérie, zone d'activités. Selon la zone dans laquelle nous nous trouvons, nous aurons plus de chances de trouver un type de bâtiment bien particulier (par exemple, en centre-ville, des tours)

Nous allons tout d'abord implémenter une disposition de zones en cercles concentriques (Centre-ville au coeur, autour périphérie et au delà zone d'activités). Puis, si nous avons le temps :

- d'autres options : ville à 100 % Centre-ville, à 100 % Périphérie, ... etc.
- Une option "Cité Personnalisée" : avant de générer une ville, l'utilisateur est invité, par le biais d'une fenêtre dans laquelle on trouvera un rectangle, représentant la surface de la ville, à dessiner les zones qu'il souhaite où il veut. La cité générée correspondra aux modifications apportées par l'utilisateur.

A noter que la surface est quadrillée par des carrés d'un mètre par un mètre. Dans chacun de ces carrés, on sait si ce dernier est occupé par une route, un bâtiment, ou tout simplement vide.

Participants : Stéphane ARCELLIER, Fatou Binetou FALL
