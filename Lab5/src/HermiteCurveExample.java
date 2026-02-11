package Lab5.src;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;

public class HermiteCurveExample extends JPanel {

    // Points P1 and P2
    private Point2D.Double P1 = new Point2D.Double(100, 300);
    private Point2D.Double P2 = new Point2D.Double(400, 100);

    // Vectors V1 and V2
    private Point2D.Double V1 = new Point2D.Double(150, 200);
    private Point2D.Double V2 = new Point2D.Double(150, 200);

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        // We draw the Hermite curve
        g2d.setColor(Color.BLUE);
        Point2D.Double prev = P1;
        for (double t = 0; t <= 1; t += 0.01) {
            double h00 = 2*t*t*t - 3*t*t + 1;
            double h01 = -2*t*t*t + 3*t*t;
            double h10 = t*t*t - 2*t*t + t;
            double h11 = t*t*t - t*t;

            double x = h00*P1.x + h10*V1.x + h01*P2.x + h11*V2.x;
            double y = h00*P1.y + h10*V1.y + h01*P2.y + h11*V2.y;

            Point2D.Double curr = new Point2D.Double(x, y);
            g2d.drawLine((int)prev.x, (int)prev.y, (int)curr.x, (int)curr.y);
            prev = curr;
        }

        // We draw control points and vectors
        g2d.setColor(Color.GREEN);
        g2d.fillOval((int)P1.x-5, (int)P1.y-5, 10, 10);
        g2d.fillOval((int)P2.x-5, (int)P2.y-5, 10, 10);

        g2d.setColor(Color.RED);
        g2d.drawLine((int)P1.x, (int)P1.y, (int)(P1.x+V1.x/2), (int)(P1.y+V1.y/2));
        g2d.drawLine((int)P2.x, (int)P2.y, (int)(P2.x+V2.x/2), (int)(P2.y+V2.y/2));
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Hermite Curve Example");
        HermiteCurveExample panel = new HermiteCurveExample();
        frame.add(panel);
        frame.setSize(600, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}