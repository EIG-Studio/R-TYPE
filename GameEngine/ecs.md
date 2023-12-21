## ECS Game Engine

### Components

- Gravity [V]
- Shooter [V]
- Behavior -<Advanced>-
- HealthPoint [V]
- Position [V]
- Velocity [V]
- Type
- Size [V]
- Renderer (Texture & Sprite)
- Damage [V]
- Speed [V]
- HitBox [V]
- ID [V]

### System

- GravitySystem -<Advanced>- (Gére la gravity de l'entitée)
- BehaviorSystem -<Advanced>- (Gére un script pour manage une entitée à la place des autres sytèmes )
- ShootingSystem -<Basic>- (Gére la création de Projectile quand une entité tire)
- DeathSystem -<Basic>- (Gére la mort des entitées)
- DamagedSystem -<Basic>- (Gére les dégats infliger)
- MovementSystem -<Basic>- (Permet de gérer les mouvements des entitées)
- IASystem -<Basic>- (Pour l'enemie, qu'il puisse tiré ou bougé)
- RendererSystem -<Basic>- (Display on client side)
- CollisionSystem -<Basic>- (Gére les collisions entre deux entités en fontion de leur type)
- NoMoveSystem -<Basic>- (Bloque l'overlap entre 2 entitées)

### Entity

Class Entity

vector any pour le compo
constructor choisir les compo à mettre dedans

### Registry

Class Registry

Vector Entities
Factory Entity ==> SendChange(NEW ID POS TYPE)
Destroy Entity ==> SendChange(ID DEAD)
Manage System (Input serveur ID Velo) ==> SendChange(ID POS)

Pour le 22 :
- Pouvoir créer le registry
- Pouvoir créer des entities
- Pouvoir choisir les components dans l'entity
- Avoir Tout les systems basiques
- Avoir le SendChange pour le serveur
- Essayer de faire en sorte d'être le plus générique
