import java.io.*;
import java.util.Scanner;

public class Frontend {
    static {
        System.loadLibrary("gamebackend");
    }

    public native void startLevel1();

    public native void startLevel2();

    public native void startLevel3();

    public native void movePlayer(String direction, String level);

    public native void performAction(String action);

    public native void performDragonAction(String action, String dragonName);

    public native void performStoreAction(String action);

    public native void performCaveAction(String monster);

    public native void exitGame();

    public static void main(String[] args) {
        Frontend frontend = new Frontend();
        try {
            // Start the backend process
            ProcessBuilder processBuilder = new ProcessBuilder(
                    "/Users/kaushalrajpuwar/dev/projects/GridHero/controller/game"); // Ensure 'backend' is in the same directory
            Process backendProcess = processBuilder.start();

            // Create input/output streams for communication
            BufferedReader backendOutput = new BufferedReader(new InputStreamReader(backendProcess.getInputStream()));
            PrintWriter backendInput = new PrintWriter(backendProcess.getOutputStream(), true);

            // Scanner for player input
            Scanner scanner = new Scanner(System.in);
            boolean fmain = true;
            System.out.println("Welcome to the Game!");
            while (fmain) {
                System.out.println("\nChoose an option:");
                System.out.println("1. Play Level 1");
                System.out.println("2. Play Level 2");
                System.out.println("3. Play Level 3");
                System.out.println("4. Exit");
                System.out.print("> ");

                String input = scanner.nextLine();
                String response;

                switch (input) {
                    case "1":
                        backendInput.println("level1");

                        while ((response = backendOutput.readLine()) != null) {
                            System.out.println("[Backend]: " + response);
                            if (response.contains(
                                    "Level 1: Avoid the enemy on the grid and collect coins as much as possible to build the town hall!")) {
                                break;
                            }
                        }

                        level1Actions(scanner, backendInput, backendOutput, frontend);
                        break;
                    case "2":
                        backendInput.println("level2");
                        while ((response = backendOutput.readLine()) != null) {
                            System.out.println("[Backend]: " + response);
                            if (response.contains("Level 2: Avoid the enemy with restricted areas!")) {
                                break;
                            }
                        }
                        level2Actions(scanner, backendInput, backendOutput, frontend);
                        break;
                    case "3":
                        backendInput.println("level3");
                        while ((response = backendOutput.readLine()) != null) {
                            System.out.println("[Backend]: " + response);
                            if (response.contains("Level 3: Welcome to the Dragon Slayer game!")) {
                                break;
                            }
                        }
                        level3Actions(scanner, backendInput, backendOutput, frontend);
                        break;
                    case "4":
                        backendInput.println("exit");
                        while ((response = backendOutput.readLine()) != null) {
                            System.out.println("[Backend]: " + response);
                            if (response.contains("Exiting game")) {
                                fmain = false;
                                break;
                            }
                        }
                        backendProcess.destroy();
                        System.out.println("Goodbye!");
                        break;
                    default:
                        System.out.println("Invalid input. Please try again.");
                        continue;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Method to handle Level 1 specific actions
    private static void level1Actions(Scanner scanner, PrintWriter backendInput, BufferedReader backendOutput, Frontend frontend)
            throws IOException {
        // Handle player movement and interactions for Level 1
        boolean flag = true;
        while (flag) {
            System.out.println("\nLevel 1 - Choose your move:");
            System.out.println("W: Move Up");
            System.out.println("A: Move Left");
            System.out.println("S: Move Down");
            System.out.println("D: Move Right");
            System.out.println("E. Exit");
            // System.out.println("E: Enter Store");
            System.out.print("> ");

            String move = scanner.nextLine();
            if (move == "E") {
                backendInput.println("exit");
                System.out.println("Goodbye!");
                return;
            }
            backendInput.println("move " + move + " " + "1"); // Send move command to backend

            // Read backend response (grid and other game status)
            String response;
            while ((response = backendOutput.readLine()) != null) {
                System.out.println("[Backend]: " + response);
                if (response.contains("Level 1 complete")) {
                    flag = false;
                    break;
                }
                if (response.contains("movement done.")) {
                    break;
                }
                if (response.contains("You exited the game")) {
                    flag = false;
                    break;
                }

            }
        }
    }

    // Method to handle Level 2 specific actions
    private static void level2Actions(Scanner scanner, PrintWriter backendInput, BufferedReader backendOutput,
            Frontend frontend)
            throws IOException {
        // Handle player movement and interactions for Level 2
        System.out.println("\nLevel 2 - Choose your move:");
        System.out.println("W: Move Up");
        System.out.println("A: Move Left");
        System.out.println("S: Move Down");
        System.out.println("D: Move Right");
        // System.out.println("E: Enter Store");
        System.out.println("E. Exit");
        System.out.print("> ");
        boolean flag2 = true;
        while (flag2) {

            String move = scanner.nextLine();
            if (move == "E") {
                backendInput.println("exit");
                System.out.println("Goodbye!");
                return;
            }
            backendInput.println("move " + move + " " + "2"); // Send move command to backend

            // Read backend response (grid and other game status)
            String response;
            while ((response = backendOutput.readLine()) != null) {
                System.out.println("[Backend]: " + response);
                if (response.contains("Level 2 complete")) {
                    flag2 = false;
                    break;
                }
                if (response.contains("movement done.")) {
                    break;
                }
                if (response.contains("You exited the game")) {
                    flag2 = false;
                    break;
                }
            }
        }

    }

    // Method to handle Level 3 specific actions (Dragon fight and Store
    // interactions)
    private static void level3Actions(Scanner scanner, PrintWriter backendInput, BufferedReader backendOutput,
            Frontend frontend)
            throws IOException {
        // Handle player fighting the dragon or entering store in Level 3
        boolean lrun = true;
        while (lrun) {
            System.out.println("\nLevel 3 - What would you like to do?");
            System.out.println("1. Fight Dragon");
            System.out.println("2. Enter Store");
            System.out.println("3. Go to Cave");
            System.out.println("4. Exit");
            System.out.print("> ");

            String action = scanner.nextLine();
            /*
             * if(action=="4"){
             * backendInput.println("exit");
             * System.out.println("Goodbye!");
             * return;
             * }
             */
            backendInput.println("action " + action); // Send action to backend

            // Read backend response for the action
            String response;
            while ((response = backendOutput.readLine()) != null) {
                System.out.println("[Backend]: " + response);
                if (response.contains("invalid choice.Try again.")) {
                    break;
                }
                if (response.contains("Fight Dragon")) {
                    fightDragon(scanner, backendInput, backendOutput, "dragon", frontend); // Start dragon fight
                    break;
                } else if (response.contains("Enter Store")) {
                    enterStore(scanner, backendInput, backendOutput, frontend); // Enter the store
                    break;
                } else if (response.contains("Go to Cave")) {
                    enterCave(scanner, backendInput, backendOutput, frontend); // Enter the cave
                    break;
                } else if (response.contains("Exit game")) {
                    lrun = false;
                    break;
                }
            }
        }
    }

    // Method for fighting the dragon
    private static void fightDragon(Scanner scanner, PrintWriter backendInput, BufferedReader backendOutput,
            String dragonName, Frontend frontend) throws IOException {
        boolean frun = true; // Flag to control the game loop
        while (frun) {
            System.out.println("\nYou are fighting the " + dragonName + " Choose an action:");
            System.out.println("1. Attack");
            System.out.println("2. Dodge");
            System.out.println("3. Go to Store");
            // System.out.println("4. Exit");
            System.out.print("> ");

            String action = scanner.nextLine();
            if (action == "4") {
                backendInput.println("exit");
                System.out.println("Goodbye!");
                return;
            }
            backendInput.println("dragon_action " + action + " " + dragonName); // Send dragon fight action to backend
            backendInput.flush();

            // Read backend response (dragon status, player status, etc.)
            String response;
            while ((response = backendOutput.readLine()) != null) {

                System.out.println("[Backend]: " + response);
                if (response.contains("invalid choice.Try again.")) {
                    break;
                }
                if (response.contains("you attacked the dragon")) {
                    break;
                }
                if (response.contains("You dodged the dragon")) {
                    break;
                }
                if (response.contains("Enter store")) {
                    enterStore(scanner, backendInput, backendOutput, frontend); // Enter the store
                    break;
                }
                if (response.contains("You defeated the dragon") || response.contains("Game over")) {
                    frun = false;
                    break;
                }

            }
        }
    }

    // Method for interacting with the store
    private static void enterStore(Scanner scanner, PrintWriter backendInput, BufferedReader backendOutput,
            Frontend frontend)
            throws IOException {
        boolean run = true;
        while (run) {
            System.out.println("\nWelcome to the store. Choose an action:");
            System.out.println("1. Buy Health");
            System.out.println("2. Buy Weapon");
            System.out.println("3. Exit Store");
            // System.out.println("4. Exit");
            System.out.print("> ");

            String action = scanner.nextLine();
            backendInput.println("store_action " + action); // Send store action to backend

            // Read backend response (store status, player inventory, etc.)
            String response;
            while ((response = backendOutput.readLine()) != null) {
                System.out.println("[Backend]: " + response);
                if (response.contains("Invalid store action!")) {
                    break;
                }
                if (response.contains("Exiting store")) {
                    break;
                }
                if (response.contains("Go back to fight")) {
                    // fightDragon(scanner, backendInput, backendOutput,"dragon");
                    run = false;
                    break;
                }

            }
        }
    }

    // Method for entering the cave and selecting the monster
    private static void enterCave(Scanner scanner, PrintWriter backendInput, BufferedReader backendOutput,
            Frontend frontend)
            throws IOException {
        boolean crun = true;
        while (crun) {
            // System.out.println("\nWelcome to the cave. Choose an opponent:");
            System.out.println("1. Slime");
            System.out.println("2. Fanged Beast");
            // System.out.println("3. Exit");
            System.out.print("> ");

            String choice = scanner.nextLine();
            if (choice == "3") {
                backendInput.println("exit");
                System.out.println("Goodbye!");
                return;
            }
            String dragonName = "";
            switch (choice) {
                case "1":
                    dragonName = "slime";
                    fightDragon(scanner, backendInput, backendOutput, "slime", frontend); // Pass dragon name
                    break;
                case "2":
                    dragonName = "FangedBeast";
                    fightDragon(scanner, backendInput, backendOutput, "FangedBeast", frontend); // Pass dragon name
                    break;
                default:
                    System.out.println("Invalid choice. Please select 1 or 2.");
                    continue;
            }
            // fightDragon(scanner, backendInput, backendOutput, frontend);

            backendInput.println("cave_action " + dragonName); // Send cave action to backend

            // Read backend response (cave battle or invalid input)
            String response;
            while ((response = backendOutput.readLine()) != null) {
                System.out.println("[Backend]: " + response);
                if (response.contains("Battle completed with " + dragonName)) {
                    // fightDragon(scanner, backendInput, backendOutput, dragonName); // Pass dragon
                    // name
                    crun = false;

                    break;
                }
                if (response.contains("Invalid monster")) {
                    break;
                }

            }
        }
    }
}
