package character;

public class CharacterMemento {

    private final int health;
    private final int level;

    public CharacterMemento(int health, int level) {
        this.health = health;
        this.level = level;
    }

    public int getHealth() {
        return health;
    }

    public int getLevel() {
        return level;
    }
}
