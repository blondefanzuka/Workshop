import java.util.Scanner;
public class Main{
    static Scanner scanner = new Scanner(System.in);
    static double balance;
    public static void main(String []args){
        menu();
        scanner.close();
    }
    static void menu() {
        System.out.println("Zuka Bank");
        System.out.println("1.Show ballance");
        System.out.println("2.Deposit");
        System.out.println("3.Withdraw");
        System.out.println("4.Exit");
        System.out.print("Enter your choice: ");
        int choice = scanner.nextInt();
        chooser(choice);
    }
    static void chooser(int choice){
            switch (choice) {
                case 1 -> showBallance();
                case 2 -> deposit();
                case 3 -> withdraw();
                case 4 -> {
                    System.out.println("Goodbye!");
                    System.exit(0);
                }
            }
            menu();
    }
    static void showBallance(){
        System.out.println(balance);
    }
    static void deposit(){
        System.out.println("Enter the amount you want to deposit: ");
        double deposit = scanner.nextDouble();
        balance += deposit;
    }
    static void withdraw(){
        System.out.println("Enter the amount you want to withdraw: ");
        double withdraw = scanner.nextDouble();
        balance -= withdraw;
    }
}
