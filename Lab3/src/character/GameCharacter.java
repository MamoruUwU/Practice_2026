package character;

public class GameCharacter {

    String type;
    public int health;
    public int level;
    Weapon weapon;

    public void show() {
        System.out.println("Type: " + type);
        System.out.println("Health: " + health);
        System.out.println("Level: " + level);
        weapon.useWeapon();
    }

    public CharacterMemento saveState() {
        return new CharacterMemento(health, level);
    }

    public void restoreState(CharacterMemento memento) {
        this.health = memento.getHealth();
        this.level = memento.getLevel();
    }
}
