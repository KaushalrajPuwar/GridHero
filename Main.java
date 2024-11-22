 package GameUI;

public class Main {
    public static void main(String[] args) {
        GameController controller = new GameController();
        //Scanner scanner = new Scanner(System.in);
        //SwingUtilities.invokeLater(GameController::new );
        //scanner.close();
        controller.startGame();
    }
}
