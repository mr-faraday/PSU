package com.cpad_lab7;

import java.io.*;
import java.util.Stack;

public class Main {
    public static void main(String[] args) throws IOException {
        Stack<Character> stack = new Stack<Character>();
        FileInputStream fileIn = null;
        FileOutputStream fileOut = null;

        try {
            fileIn = new FileInputStream("in.txt");
            fileOut = new FileOutputStream("out.txt");

            BufferedReader br = new BufferedReader(new InputStreamReader(fileIn, "utf-8"));
            StringBuilder sb = new StringBuilder();
            String line;

            while(( line = br.readLine()) != null ) {
                for (int i = 0; i < line.length(); i++) {
                    stack.push(line.charAt(i));
                }

                stack.push( '\n' );
            }

            while (!stack.empty()) {
                fileOut.write(stack.pop());
            }

            System.out.println();
        } finally {
            if (fileIn != null) {
                fileIn.close();
            }
            if (fileOut != null) {
                fileOut.close();
            }
        }
    }
}
