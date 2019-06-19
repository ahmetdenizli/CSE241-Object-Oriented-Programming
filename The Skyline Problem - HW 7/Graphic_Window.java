/*##############################################*/
/*                Ahmet Denizli                 */
/*                  161044020                   */
/*##############################################*/
package skyline_;

import java.awt.Color; 
import java.awt.Container; 
import java.util.ArrayList;
import javax.swing.JFrame; 
import javax.swing.JPanel; 

public class Graphic_Window extends JFrame 
{ 
        // x for critical pts, y for max pts, z for min points
      public Graphic_Window(ArrayList<Integer> x, ArrayList<Integer> y, ArrayList<Integer> z, ArrayList<Integer> que_pts) 
      { 
              this.setTitle("Graphic Window"); 
              this.setSize(1280 , 800); 
              this.setLayout(null); 
              BilesenleriEkle(this.getContentPane(), x, y, z, que_pts); 
              this.setVisible(true); 
              this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
      } 

      public static void BilesenleriEkle(Container pencere, ArrayList<Integer> x, ArrayList<Integer> y, ArrayList<Integer> z, ArrayList<Integer> que_pts) 
      { 
              for (int i = 0; i < x.size(); i++) {
                  JPanel Panel = new JPanel();
                  pencere.add(Panel); 
                  Panel.setBackground(Color.RED); 
                  Panel.setBounds(x.get(i)*20, 400-20*y.get(i), 5, 20*(y.get(i)-z.get(i)) );
              }
              int high=0, k=1;
              for (int i = 0; i < x.size()-1; i++) {
                  JPanel Panel = new JPanel();
                  pencere.add(Panel); 
                  Panel.setBackground(Color.RED); 
                  high +=(que_pts.get(k)-que_pts.get(k-1));
                  Panel.setBounds(x.get(i)*20, 400-20*high, 20*(x.get(i+1)-x.get(i))+5, 5 );
                  k+=2;
              }
      }
}