import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while (input.hasNext()) {
			long array[] = new long[6];
			for (int index = 5; index >= 0; index--) {
				array[index] = input.nextLong();
			}
			boolean flag = false;
			for (int index = 0; index < 6; index++) {
				if(flag)System.out.print(" ");
				else flag = true;
				System.out.print(array[index]);
			}
			System.out.println();
		}
		input.close();
	}

}
