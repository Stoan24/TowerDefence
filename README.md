# TowerDefence
TD game for school

Have a path of waypoints
Let the enemies follow that path
Let the player place towers on certain spots
Then make the towers shoot at the enemies


--Skill Menu--
Player can choose a skill or relic that boosts their gameplay in some sort of way


'Gameplay'
---Before the round--
Skill menu pops
player can choose to start round or place towers

--Round start--
Enemies spawn and walk the path
Turrets shoot the enemies

PLAYER
has:
-lifepoints

can:
--> press button to start the round
--> place towers along spaces

ENEMY
has:
-lifepoints
-damage

can:
--> move
--> When reached the end, then lose lifepoint according to damage
--> when hit, take damage
--> lifepoints = 0, then die

TOWERLOCATIONS
has:
-position
-tower or not

TOWERS

has:
-position
-range
-damage

can:
--> get placed on towerlocation
--> when enemy inside range, then shoot
