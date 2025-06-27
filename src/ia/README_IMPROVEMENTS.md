# Améliorations de l'IA Zappy

## Vue d'ensemble

Cette IA Zappy a été considérablement améliorée pour être plus proche des spécifications du projet et plus efficace dans sa stratégie de jeu. Les améliorations incluent une meilleure gestion des œufs (fork), une stratégie de survie optimisée, et une coordination d'équipe avancée.

## Nouvelles fonctionnalités implémentées

### 1. Gestion des œufs (Fork Strategy)

**Problème résolu :** L'IA originale ne gérait pas la reproduction (fork) qui est essentielle pour créer une équipe de 6 joueurs niveau 8.

**Solution :** 
- Implémentation de `shouldFork()` qui détermine quand créer un œuf
- Stratégie de fork aux niveaux 2, 4, et 6 (niveaux stratégiques)
- Condition : avoir plus de 10 unités de nourriture pour assurer la survie

```cpp
bool DecisionEngine::shouldFork(int level, const std::map<ResourceType, int>& inventory) {
    return (level >= 2 && inventory.at(ResourceType::FOOD) > 10 && 
            (level == 2 || level == 4 || level == 6));
}
```

### 2. Stratégie de survie améliorée

**Problème résolu :** Gestion basique de la nourriture avec seuil trop bas.

**Solution :**
- Seuil de survie augmenté à 3 unités de nourriture (au lieu de 2)
- Priorité absolue donnée à la survie avant toute autre action
- Exploration intelligente pour trouver de la nourriture

### 3. Collecte de ressources optimisée

**Problème résolu :** L'IA ne savait pas quelles ressources collecter selon son niveau.

**Solution :**
- Implémentation de `getNeededResourceForLevel()` qui retourne la ressource manquante
- Collecte ciblée au lieu d'exploration aléatoire

### 4. Coordination d'équipe

**Nouvelles fonctionnalités :**
- Système de broadcast pour partager position et niveau
- Traitement des messages d'équipe (aide, incantation, statut)
- Communication périodique pour coordination

### 5. Gestion avancée des réponses serveur

**Améliorations :**
- Traitement des réponses d'élévation ("Elevation underway", "Current level")
- Gestion des échecs de commandes ("ko")
- Traitement des éjections par d'autres joueurs
- Mise à jour automatique de l'état du jeu

### 6. Exploration intelligente

**Problème résolu :** Mouvements purement aléatoires inefficaces.

**Solution :**
- Évitement des mouvements répétitifs
- Utilisation de la commande Look pour analyser l'environnement
- Adaptation des mouvements selon les informations visuelles

## Corrections des bugs

### 1. Stratégie d'élévation
- **Bug :** Conditions incorrectes pour les niveaux 3 et 4
- **Fix :** Correction des ressources requises selon les spécifications Zappy

### 2. Gestion des types
- **Bug :** Erreurs de conversion tuple/pair
- **Fix :** Conversion appropriée des positions

### 3. Ordre d'initialisation
- **Bug :** Erreur d'ordre des membres dans GameState
- **Fix :** Réorganisation des déclarations

## Architecture améliorée

### Nouvelles méthodes dans DecisionEngine

```cpp
// Stratégie de reproduction
bool shouldFork(int level, const std::map<ResourceType, int>& inventory);

// Gestion des ressources
ResourceType getNeededResourceForLevel(int level, const std::map<ResourceType, int>& inventory);
void exploreForResource(ResourceType resource);

// Coordination d'équipe
bool shouldBroadcast();
void processTeamMessage(int direction, const std::string& message);

// Gestion avancée des réponses
void updateVisionData(const std::vector<std::vector<std::string>>& tiles);
void handleFailedCommand();
void updatePlayerLevel(const std::string& response);
void handleEjection();

// Exploration intelligente
void intelligentExploration();
```

## Priorités de l'IA (ordre d'exécution)

1. **Survie** - Collecter de la nourriture si < 3 unités
2. **Reproduction** - Fork aux niveaux stratégiques si conditions remplies
3. **Élévation** - Incantation si toutes les conditions sont réunies
4. **Collecte** - Ramasser les ressources nécessaires pour le niveau actuel
5. **Coordination** - Communiquer avec l'équipe
6. **Exploration** - Mouvement intelligent pour découvrir de nouvelles ressources

## Spécifications Zappy respectées

- ✅ Gestion des 7 types de ressources
- ✅ Conditions d'élévation exactes pour chaque niveau (1→8)
- ✅ Système de fork pour créer des œufs
- ✅ Coordination d'équipe via broadcast
- ✅ Gestion de la survie (nourriture)
- ✅ Objectif : 6 joueurs niveau 8

## Performance attendue

Avec ces améliorations, l'IA devrait :
- Survivre plus longtemps grâce à une meilleure gestion de la nourriture
- Progresser plus rapidement vers les niveaux supérieurs
- Créer une équipe complète grâce au système de fork
- Coordonner efficacement les incantations d'équipe
- Atteindre l'objectif de victoire (6 joueurs niveau 8)

## Utilisation

```bash
# Compilation
make

# Lancement (exemple)
./zappy_ai -p 4242 -n team_name -h localhost
```