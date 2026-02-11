package character;

public class WarriorBuilder implements CharacterBuilder {

    private GameCharacter character = new GameCharacter();

    @Override
    public void buildType() {
        character.type = "Warrior";
    }

    @Override
    public void buildHealth() {
        character.health = 150;
    }

    @Override
    public void buildLevel() {
        character.level = 1;
    }

    @Override
    public void buildWeapon() {
        character.weapon = new Bow();
    }

    @Override
    public GameCharacter getCharacter() {
        return character;
    }
}
