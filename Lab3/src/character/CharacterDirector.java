package character;

public class CharacterDirector {
    public void construct(CharacterBuilder builder) {
        builder.buildType();
        builder.buildHealth();
        builder.buildLevel();
        builder.buildWeapon();
    }
}
