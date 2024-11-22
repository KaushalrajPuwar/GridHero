import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.util.Queue;

public class GridGameGUI extends JFrame {
    static final int GRID_SIZE = 10; // Grid size
    static final char EMPTY = '.';
    static final char PLAYER = 'P';
    static final char ENEMY = 'E';
    static final char INACCESSIBLE = 'x'; // Inaccessible blocks

    static final int INF = Integer.MAX_VALUE;
    static final int[][] playerDirections = {
            { -1, 0 }, // up
            { 1, 0 }, // down
            { 0, -1 }, // left
            { 0, 1 } // right
    };

    static final int[][] enemyDirections = {
            { -1, 0 }, // up
            { 1, 0 }, // down
            { 0, -1 }, // left
            { 0, 1 }, // right
            { -1, -1 }, // top-left
            { -1, 1 }, // top-right
            { 1, -1 }, // bottom-left
            { 1, 1 } // bottom-right
    };

    private char[][] grid;
    private int[] playerPos;
    private int[] previousPlayerPos;
    private int[] enemyPos;
    private JLabel[][] gridLabels;
    private int stepCounter = 0;

    // Load and scale images
    private ImageIcon playerIcon = scaleImageIcon(new ImageIcon("player.png"));
    private ImageIcon enemyIcon = scaleImageIcon(new ImageIcon("enemy.png"));
    private ImageIcon wallIcon = scaleImageIcon(new ImageIcon("wall.png"));

    public GridGameGUI() {
        grid = new char[GRID_SIZE][GRID_SIZE];
        playerPos = new int[] { 0, 0 };
        previousPlayerPos = new int[] { -1, -1 };
        enemyPos = new int[] { GRID_SIZE - 1, GRID_SIZE - 1 };

        initializeGrid(grid, playerPos, enemyPos);
        initializeUI();
    }

    private void initializeUI() {
        setTitle("Grid Game");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel gridPanel = new JPanel(new GridLayout(GRID_SIZE, GRID_SIZE));
        gridLabels = new JLabel[GRID_SIZE][GRID_SIZE];

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                gridLabels[i][j] = new JLabel();
                gridLabels[i][j].setHorizontalAlignment(SwingConstants.CENTER);
                gridLabels[i][j].setBorder(BorderFactory.createLineBorder(Color.BLACK));
                gridLabels[i][j].setOpaque(true);
                gridLabels[i][j].setBackground(Color.WHITE);
                updateLabelIcon(i, j); // Set the initial icon
                gridPanel.add(gridLabels[i][j]);
            }
        }

        add(gridPanel, BorderLayout.CENTER);

        JPanel controlPanel = new JPanel();
        JButton upButton = new JButton("Up");
        JButton downButton = new JButton("Down");
        JButton leftButton = new JButton("Left");
        JButton rightButton = new JButton("Right");
        JButton quitButton = new JButton("Quit");

        controlPanel.add(upButton);
        controlPanel.add(downButton);
        controlPanel.add(leftButton);
        controlPanel.add(rightButton);
        controlPanel.add(quitButton);
        add(controlPanel, BorderLayout.SOUTH);

        upButton.addActionListener(e -> handleMove('w'));
        downButton.addActionListener(e -> handleMove('s'));
        leftButton.addActionListener(e -> handleMove('a'));
        rightButton.addActionListener(e -> handleMove('d'));
        quitButton.addActionListener(e -> System.exit(0));

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private ImageIcon scaleImageIcon(ImageIcon icon) {
        Image img = icon.getImage();
        Image scaledImg = img.getScaledInstance(50, 50, Image.SCALE_SMOOTH); // Adjust size as needed
        return new ImageIcon(scaledImg);
    }

    private void initializeGrid(char[][] grid, int[] playerPos, int[] enemyPos) {
        for (int i = 0; i < GRID_SIZE; i++) {
            Arrays.fill(grid[i], EMPTY);
        }

        int[][] inaccessibleBlocks = {
                { 0, 5 }, { 1, 2 }, { 1, 7 }, { 2, 4 }, { 3, 0 }, { 3, 6 },
                { 4, 4 }, { 5, 2 }, { 5, 8 }, { 6, 1 }, { 7, 3 }, { 8, 5 },
                { 8, 6 }, { 9, 2 }
        };

        for (int[] block : inaccessibleBlocks) {
            int x = block[0];
            int y = block[1];
            grid[x][y] = INACCESSIBLE;
        }

        grid[playerPos[0]][playerPos[1]] = PLAYER;
        grid[enemyPos[0]][enemyPos[1]] = ENEMY;
    }

    private void updateGrid() {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                updateLabelIcon(i, j);
            }
        }
    }

    private void updateLabelIcon(int i, int j) {
        if (grid[i][j] == PLAYER) {
            gridLabels[i][j].setIcon(playerIcon);
            gridLabels[i][j].setBackground(Color.WHITE);
        } else if (grid[i][j] == ENEMY) {
            gridLabels[i][j].setIcon(enemyIcon);
            gridLabels[i][j].setBackground(Color.WHITE);
        } else if (grid[i][j] == INACCESSIBLE) {
            gridLabels[i][j].setIcon(wallIcon);
            gridLabels[i][j].setBackground(Color.WHITE);
        } else {
            gridLabels[i][j].setIcon(null);
            gridLabels[i][j].setBackground(Color.WHITE);
        }
    }

    private boolean isValidPosition(int x, int y) {
        return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] != INACCESSIBLE;
    }

    private void handleMove(char move) {
        int newX = playerPos[0];
        int newY = playerPos[1];

        if (move == 'w')
            newX--;
        else if (move == 's')
            newX++;
        else if (move == 'a')
            newY--;
        else if (move == 'd')
            newY++;

        if (isValidPosition(newX, newY)) {
            if (newX == previousPlayerPos[0] && newY == previousPlayerPos[1]) {
                JOptionPane.showMessageDialog(this,
                        "Invalid move! You cannot move back to the previous cell directly.");
                return;
            }

            grid[playerPos[0]][playerPos[1]] = EMPTY;
            previousPlayerPos[0] = playerPos[0];
            previousPlayerPos[1] = playerPos[1];
            playerPos[0] = newX;
            playerPos[1] = newY;
            grid[playerPos[0]][playerPos[1]] = PLAYER;

            moveEnemy();
            updateGrid();

            stepCounter++; // Increment the step counter after the player moves

            if (Arrays.equals(playerPos, enemyPos)) {
                JOptionPane.showMessageDialog(this, "Caught by the enemy! Game Over!\nTotal steps: " + stepCounter);
                System.exit(0);
            }
        } else {
            JOptionPane.showMessageDialog(this,
                    "Invalid move! You can't move onto an inaccessible block or outside the grid.");
        }
    }

    private void moveEnemy() {
        grid[enemyPos[0]][enemyPos[1]] = EMPTY;
        int[] newEnemyPos = calculateEnemyMove(); // Calculate best move for the enemy
        enemyPos[0] = newEnemyPos[0];
        enemyPos[1] = newEnemyPos[1];
        grid[enemyPos[0]][enemyPos[1]] = ENEMY;
    }

    private int[] calculateEnemyMove() {
        int[][] dist = new int[GRID_SIZE][GRID_SIZE];
        for (int[] row : dist)
            Arrays.fill(row, INF);

        Queue<int[]> queue = new LinkedList<>();
        queue.add(playerPos);
        dist[playerPos[0]][playerPos[1]] = 0;

        // BFS to calculate shortest path to player
        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            for (int[] dir : enemyDirections) { // Use enemy's directions (including diagonals)
                int nx = current[0] + dir[0];
                int ny = current[1] + dir[1];
                if (isValidPosition(nx, ny) && dist[nx][ny] == INF) {
                    dist[nx][ny] = dist[current[0]][current[1]] + 1;
                    queue.add(new int[] { nx, ny });
                }
            }
        }

        // Find the best move based on shortest distance
        int shortestDist = INF;
        int[] bestMove = Arrays.copyOf(enemyPos, 2);
        for (int[] dir : enemyDirections) { // Check all directions for enemy's move
            int nx = enemyPos[0] + dir[0];
            int ny = enemyPos[1] + dir[1];
            if (isValidPosition(nx, ny) && dist[nx][ny] < shortestDist) {
                shortestDist = dist[nx][ny];
                bestMove[0] = nx;
                bestMove[1] = ny;
            }
        }

        return bestMove;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(GridGameGUI::new);
    }
}
