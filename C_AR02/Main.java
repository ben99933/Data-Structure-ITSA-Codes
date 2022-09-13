import java.util.Scanner;

public class Main {

	/* 
	 * 題目規定輸入六個數字(固定6個) 然後以相反的順序輸出
	 * 那我就先反著將數字存入陣列
	 * 輸出的時候順著輸出就好
	 */
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while (input.hasNext()) {
			long array[] = new long[6];
			//從index=5到index=0反向指派
			for (int index = 5; index >= 0; index--) {
				array[index] = input.nextLong();
			}
			boolean space = false;//控制是否要print空白
			for (int index = 0; index < 6; index++) {
				if(space)System.out.print(" ");
				else space = true;
				System.out.print(array[index]);
			}
			System.out.println();
		}
		input.close();
	}
}
