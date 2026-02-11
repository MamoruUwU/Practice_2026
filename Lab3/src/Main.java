
import character.CharacterBuilder;
import character.CharacterDirector;
import character.Caretaker;
import character.GameCharacter;
import character.WarriorBuilder;

public class Main {
    public static void main(String[] args) {

        CharacterDirector director = new CharacterDirector();
        CharacterBuilder builder = new WarriorBuilder();
        director.construct(builder);

        GameCharacter character = builder.getCharacter();
        character.show();

        Caretaker caretaker = new Caretaker();

        // Збереження стану
        caretaker.save(character.saveState());

        // Зміна стану
        character.health = 50;
        character.level = 2;

        System.out.println("\nAfter battle:");
        character.show();

        // Відновлення стану
        character.restoreState(caretaker.undo());

        System.out.println("\nAfter restore:");
        character.show();
    }
}
