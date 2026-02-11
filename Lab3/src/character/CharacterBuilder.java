package character;

public interface CharacterBuilder {
    void buildType();
    void buildHealth();
    void buildLevel();
    void buildWeapon();
    GameCharacter getCharacter();
}
