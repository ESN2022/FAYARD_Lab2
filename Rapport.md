<h1>Lab 2 : 7 Segment counter handling with timers</h1> 


Lors de ce second TP, les 7 segments de la cible employée, c’est-à-dire la DE10-Lite d’Intel, vont être contrôlé pour afficher un compteur obtenu à l’aide d’un timer.


<h2>I.	Architecture du système</h2>

Le système de co-design comprend le softcore NIOS II, de la mémoire de type RAM, un module UART, un PIOs (Parallel I/O) relié à un décodeur binaire à 7-segment puis aux 7-segment. Ces IPs communiquent par le bus Avalon Memory Map c’est-à-dire que chaque périphérique est contrôlé en lisant ou en écrivant à ses adresses. Il y a également un timer relié directement au softcore par une ligne d’interruption. Ce dernier va servir de compteur. Chaque seconde, il va déclencher une interruption. La routine associée va permettre de compter en incrémentant un compteur dont la valeur est affichée sur les 7 segments. L’ensemble de l’architecture est résumé sur la Figure 1. 

![arch_system2](https://user-images.githubusercontent.com/103188608/212013759-371d0173-adbe-4b65-8ab1-e81e0c5300eb.png)

Le décodeur 7-segment est nécessaire pour convertir un nombre binaire en BCD. Ce fichier VHDL correspond à une simple table de vérité. Pour pouvoir compter de 0 à 9 soit 10 chiffres, 4 bits sont nécessaires (23=8 - > X ; 24=16 - > V). Pour gérer les 3 7-segment dont nous avons besoin, chaque 7-segment se voit attribuer 4 bits du PIO qui doit donc avoir 3 x 4 = 12 bits.


<h2>II.	Progression et résultat</h2>

Dans le premier commit, un compteur est incrémenté toutes les 100 ms jusqu’à arriver à 9 puis retombe à 0. La valeur de ce compteur est affichée sur un 7-segment. 

https://user-images.githubusercontent.com/103188608/212013885-4b14590e-a18e-47fa-9fcf-170cbb75bc7b.mov

La première difficulté rencontrée lors de ce second TP a été d’intégrer le composant crée. En effet, il faut faire attention à l’instanciation crée automatiquement dans « Platform Designer » qui n’est plus forcément la bonne et doit être adaptée. Ici, par exemple, la sortie du système n’est plus celle du PIO mais celle du composant crée.


Le second commit est le même que le premier mais le compteur va jusque 999 et s’affiche sur 3 7-segment. 

https://user-images.githubusercontent.com/103188608/212013981-cceaf528-4a2e-4e0f-85ab-6de883234abd.mov

Le dernier commit est celui où le compteur est réalisé avec l’IP timer. Le compteur est incrémenté à chaque fois que le timer retourne à zéro et donc génère une interruption ce qui correspond pour nous à 1 seconde. 

https://user-images.githubusercontent.com/103188608/212182444-cebfdcb6-a99f-4429-8b8a-85288ee873b1.mov

Nous avons rencontré plusieurs difficultés qui doivent à l’avenir être des points de vigilance. Nous vous les présentons dans les lignes suivantes. Il faut bien fixer la période dans l’IP QSYS en cochant « fixed period » pour ne pas avoir à gérer cela dans le soft. L’interruption d’un timer est très différente de celle d’un PIO et n’utilise pas du tout les mêmes types de fonctions. Ici, les deux registres principaux à manipuler sont le « status » notamment avec le bit « TO » qui permet de remettre à zéro l’interruption et le « control » où il est possible de choisir la manière de compter (bit « CONT »), activer l’interruption (bit « ITO ») et de débuter le compteur (bit « START »). Il faut être très vigilant sur les opérateurs bit à bit et logique qui se ressemble énormément mais ne donne pas du tout le même résultat. Par exemple, nous avions utilisé par erreur le « OU » logique « || » entre les masques des différents bits, ce qui a eu pour conséquence de renvoyer la valeur VRAI donc 1 alors que nous souhaitions régler la valeur du registre à 7. Visuellement, le compteur passait de 0 à 1 puis se stoppait. En remplaçant par l’opérateur « OU » bit à bit « | », le problème a été résolu.


<h2>Conclusion</h2>

Ce TP a été l’occasion de bien comprendre l’ensemble du flow de co-design avec un FPGA et un Nios II. Il a également permis de mettre en place des IP très régulièrement utilisée tel que des 7-segment, des timers ou encore des interruptions. Mais aussi, d’ajouter un composant crée au design. Un des points clés est également la familiarisation avec les fonctions HAL.

