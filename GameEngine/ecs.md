## ECS Game Engine

### Components

- Gravity [V]
- Shooter [V]
- Behavior -<Advanced>-
- HealthPoint [V]
- Position [V]
- Velocity [V]
- Type [V] -> change en Compo Tags -<Advanced>-
- Size [V]
- Renderer (Texture & Sprite) [V]
- Damage [V]
- Speed [V]
- HitBox [V]
- ID [V]

### System

- GravitySystem -<Advanced>- (Gére la gravity de l'entitée)
- BehaviorSystem -<Advanced>- (Gére un script pour manage une entitée à la place des autres sytèmes )
- ShootingSystem -<Basic>- (Gére la création de Projectile quand une entité tire) [V]
- DeathSystem -<Basic>- (Gére la mort des entitées) [V]
- DamagedSystem -<Basic>- (Gére les dégats infliger) [V]
- MovementSystem -<Basic>- (Permet de gérer les mouvements des entitées) [V]
- IASystem -<Basic>- (Pour l'enemie, qu'il puisse tiré ou bougé) []
- RendererSystem -<Basic>- (Display on client side) [V]
- CollisionSystem -<Basic>- (Gére les collisions entre deux entités en fontion de leur type) [V]
- NoMoveSystem -<Basic>- (Bloque l'overlap entre 2 entitées) [V]
- InputSystem -<Advanced>- (Gére les changement pour le jeu) []

### Entity

Class Entity [V]

vector any pour le compo [V]
constructor choisir les compo à mettre dedans [V]

### Registry

Class Registry [V]

Vector Entities [V]
Factory Entity ==> SendChange(NEW ID POS TYPE) [V]
Destroy Entity ==> SendChange(ID DEAD) [V]
Manage System (Input serveur ID Velo) ==> SendChange(ID POS)

Pour le 22 :
- Pouvoir créer le registry [V]
- Pouvoir créer des entities [V]
- Pouvoir choisir les components dans l'entity [V]
- Avoir Tout les systems basiques [V]
- Avoir le SendChange pour le serveur
- Essayer de faire en sorte d'être le plus générique
