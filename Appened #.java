/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;
import java.io.*; 

/**
 *
 * @author yangz
 */
public class JavaApplication1 {

    /**
     * @param args the command line arguments
     */
 public static void main(String[] args)throws Exception 
  { 
  // We need to provide file path as the parameter: 
  // double backquote is to avoid compiler interpret words 
  // like \test as \t (ie. as a escape sequence) 
  File file = new File("C:\\Users\\yangz\\Documents\\GitHub\\brute-force-key-finder\\words.txt"); 
  
  BufferedReader br = new BufferedReader(new FileReader(file)); 
  BufferedWriter writer = new BufferedWriter(new FileWriter("C:\\Users\\yangz\\Documents\\GitHub\\brute-force-key-finder\\newWords.txt"));
  
  String st; 
  while ((st = br.readLine()) != null) 
  {
    while(st.length()<16)
      {
          st=st.concat("#");
      }
    System.out.println(st); 
    writer.append(st+"\n");
  }

  }
    
}
