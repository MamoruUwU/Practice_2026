package character;
import java.util.Stack;

public class Caretaker {

    private Stack<CharacterMemento> history = new Stack<>();

    public void save(CharacterMemento memento) {
        history.push(memento);
    }

    public CharacterMemento undo() {
        if (!history.isEmpty()) {
            return history.pop();
        }
        return null;
    }
}
