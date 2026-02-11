package Lab5.src;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class FernFractal extends JFrame {

    private int A = 5;
    private int K = 6;

    public FernFractal() {

        setTitle("Fractal Fern");
        setSize(800, 650);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel control = new JPanel();
        control.setBackground(Color.DARK_GRAY);

        JTextField fieldA = new JTextField("5", 4);
        JTextField fieldK = new JTextField("6", 4);
        JButton draw = new JButton("Draw");

        draw.setBackground(new Color(0,120,215));
        draw.setForeground(Color.WHITE);

        control.add(new JLabel("A:")).setForeground(Color.WHITE);
        control.add(fieldA);
        control.add(new JLabel("K:")).setForeground(Color.WHITE);
        control.add(fieldK);
        control.add(draw);

        JPanel canvas = new JPanel() {

            Random rand = new Random();

            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2 = (Graphics2D) g;
                g2.setStroke(new BasicStroke(2));

                int cx = getWidth() / 2;
                int cy = getHeight() - 40;

                double step = 360.0 / A;

                for (int i = 0; i < A; i++) {
                    double angle = Math.toRadians(i * step - 90);
                    Color color = new Color(
                            rand.nextInt(256),
                            rand.nextInt(256),
                            rand.nextInt(256)
                    );
                    drawFern(g2, cx, cy, 100, angle, K, color);
                }
            }

            private void drawFern(Graphics2D g,
                                  double x, double y,
                                  double len,
                                  double angle,
                                  int order,
                                  Color color) {

                if (order == 0) return;

                double x2 = x + len * Math.cos(angle);
                double y2 = y + len * Math.sin(angle);

                g.setColor(color);
                g.drawLine((int)x, (int)y, (int)x2, (int)y2);

                drawFern(g, x2, y2, len*0.7, angle-0.4, order-1, color);
                drawFern(g, x2, y2, len*0.7, angle+0.4, order-1, color);
                drawFern(g, x2, y2, len*0.8, angle, order-1, color);
            }
        };

        canvas.setBackground(Color.BLACK);

        draw.addActionListener(e -> {
            A = Integer.parseInt(fieldA.getText());
            K = Integer.parseInt(fieldK.getText());
            canvas.repaint();
        });

        add(control, BorderLayout.NORTH);
        add(canvas, BorderLayout.CENTER);

        setVisible(true);
    }

    public static void main(String[] args) {
        new FernFractal();
    }
}
