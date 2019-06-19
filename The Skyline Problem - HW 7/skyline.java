/*##############################################*/
/*                Ahmet Denizli                 */
/*                  161044020                   */
/*##############################################*/
package skyline_;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;


public class skyline {

    public static void main(String[] args) throws java.io.IOException {
        File f = new File("data.txt");                                      // File object for data.txt
        
        try {
            FileReader fr = new FileReader(f);                              // FileReader object for reading data.txt
            Scanner scan = new Scanner(f);                                  // Scanner for scan data in data.txt
            
            ArrayList<Integer> width = new ArrayList<Integer>();            // Array list for width of rectangles
            ArrayList<Integer> height = new ArrayList<Integer>();           // Array list for height of rectangles
            ArrayList<Integer> position = new ArrayList<Integer>();         // Array list for position of rectangles
            ArrayList<Integer> crtcl_points = new ArrayList<Integer>();     // Array list for critical points of skyline
            // While scan hasNext
            while(scan.hasNext()){
                width.add(scan.nextInt());                                  // Add width of rectangles to width list
                height.add(scan.nextInt());                                 // Add height of rectangles to height list
                position.add(scan.nextInt());                               // Add position of rectangles to position list
            }
            fr.close(); // Closing fileReader object
            
            int cont1,cont2; // control variables
            for (int i = 0; i < position.size(); i++) {   // Compare all rectangles to others
                cont1=0; cont2=0;
                for (int j = 0; j < position.size(); j++) {
                    // If any rectangle edge contains the other rectangle's left edge then cont1=1 and break for loop
                    if(position.get(j) < position.get(i) && (position.get(j)+width.get(j)) > position.get(i) && height.get(j) > height.get(i)){
                        cont1=1;
                        break;
                    }
                    // If any rectangle edge contains the other rectangle's left edge then cont1=1 and break for loop
                    if( position.get(j) < (position.get(i)+width.get(i)) && (position.get(j)+width.get(j)) > (position.get(i)+width.get(i)) && height.get(j) > height.get(i)){
                        cont2=1;
                        break;
                    }
                }
                //If cont1==0 and crtcl_points dont contains position then add this position
                if(cont1==0)
                    if(!crtcl_points.contains(position.get(i)))
                        crtcl_points.add(position.get(i));
                //If cont2==0 and crtcl_points dont contains position then add this position
                if(cont2==0)
                    if(!crtcl_points.contains(position.get(i)+width.get(i)))
                        crtcl_points.add(position.get(i)+width.get(i));
            }
            Collections.sort(crtcl_points); // Sorting Critical points array
            
            Integer max, right_max, left_max, right_index = 0, left_index = 0;
            ArrayList<Integer> max_pts = new ArrayList<Integer>();          // Array list for maximum height of critical points
            ArrayList<Integer> min_pts = new ArrayList<Integer>();          // Array list for minmum height of critical points
            for(Integer k : crtcl_points){                                  // For each critical points search max and min height
                max=0; right_max=0 ; left_max=0;
                for (int j = 0; j < position.size(); j++) {
                    if(position.get(j) <= k && (position.get(j)+width.get(j)) >= k ){
                        if( height.get(j) > max)                            // Find maximum height on critical points
                            max = height.get(j);
                    }
                    if(position.get(j) <= k+1 && (position.get(j)+width.get(j)) >= k+1 ){   // Find maximum height on critical points right
                        if( height.get(j) > right_max){
                            right_max = height.get(j);
                            right_index = j;
                        }
                    }
                    if(position.get(j) <= k-1 && (position.get(j)+width.get(j)) >= k-1 ){   // Find maximum height on critical points left
                        if( height.get(j) > left_max){
                            left_max = height.get(j);
                            left_index = j;
                        }
                    }
                }
                max_pts.add(max);           // Add maximum height of critical points to max_pts
                if(Objects.equals(max, left_max)){
                    if( (position.get(right_index))<= k)
                        min_pts.add(right_max);           // Add minimum height of critical points to min_pts
                    else
                        min_pts.add(0);
                }
                else if(Objects.equals(max, right_max)){
                    if( position.get(left_index)+width.get(left_index)>=k )
                        min_pts.add(left_max);           // Add minimum height of critical points to min_pts
                    else
                        min_pts.add(0);
                }
                else
                    min_pts.add(0);
            }
            
            ArrayList<Integer> que_pts = new ArrayList<Integer>(); // Max and min queued list
            int up; // 1 for max stage 2 for down stage
            System.out.printf("(%d, %d)",  crtcl_points.get(0), min_pts.get(0));    // Print corner to standard output with ordered
            que_pts.add(min_pts.get(0));                                            // add ordered corners to que points
            System.out.printf(", (%d, %d)",  crtcl_points.get(0), max_pts.get(0));  // Print corner to standard output with ordered
            que_pts.add(max_pts.get(0));                                            // add ordered corners to que points
            up=1;
            for (int i = 1; i < crtcl_points.size(); i++) {                         // Print corners to standard output with ordered
                switch(up){                                                         // add ordered corners to que points
                    case 1:
                        if( Objects.equals(max_pts.get(i), max_pts.get(i-1)) ){
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), max_pts.get(i));
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), min_pts.get(i));
                            que_pts.add(max_pts.get(i));
                            que_pts.add(min_pts.get(i));
                            up=2;
                        }
                        else if ( Objects.equals(min_pts.get(i), max_pts.get(i-1)) ){
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), min_pts.get(i));
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), max_pts.get(i));
                            que_pts.add(min_pts.get(i));
                            que_pts.add(max_pts.get(i));
                            up = 1;
                        }
                        break;
                    case 2:
                        if( Objects.equals(max_pts.get(i), min_pts.get(i-1)) ){
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), max_pts.get(i));
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), min_pts.get(i));
                            que_pts.add(max_pts.get(i));
                            que_pts.add(min_pts.get(i));
                            up=2;
                        }
                        else if ( Objects.equals(min_pts.get(i), min_pts.get(i-1)) ){
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), min_pts.get(i));
                            System.out.printf(", (%d, %d)",  crtcl_points.get(i), max_pts.get(i));
                            que_pts.add(min_pts.get(i));
                            que_pts.add(max_pts.get(i));
                            up = 1;
                        }
                        break;
                }
            }
            new Graphic_Window( crtcl_points, max_pts, min_pts, que_pts); // Call Grapic_Window.java for show the skyline
        } 
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}