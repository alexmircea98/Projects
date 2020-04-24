import java.io.File;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        int books, libraries, days, daysPassed = 0, value = 0;
        File file = new File("src/a_example");
        Scanner sc;
        try {
            sc = new Scanner(file);
        }
        catch (Exception e) {
            System.out.println("am prins exceptia");
            return;
        }
        books = sc.nextInt();
        libraries = sc.nextInt();
        days = sc.nextInt();
        List<Book> bookValues = new ArrayList<>();
        List<Boolean> scannedBooks = new ArrayList<>(Arrays.asList(new Boolean[books]));
        Collections.fill(scannedBooks, Boolean.FALSE);
        List<Library> libraryList = new ArrayList<Library>();
        for (int i = 0; i < books; ++i) {
            bookValues.add(new Book(i, sc.nextInt()));
        }
        for (int i = 0; i < libraries; ++i) {
            int libraryBooks = sc.nextInt();
            libraryList.add(new Library(libraryBooks, sc.nextInt(), sc.nextInt()));
            for (int j = 0; j < libraryBooks; ++j) {
                int bookId = sc.nextInt();
                libraryList.get(i).bookList.add(bookValues.get(bookId));
            }
            Collections.sort(libraryList.get(i).bookList, new ValueComparator());
        }
        for (int i = 0; i < libraries; ++i) {
            for (int j = 0; j < libraryList.get(i).numberOfBooks; ++j) {
                System.out.print(libraryList.get(i).bookList.get(j).value + " ");
            }
            System.out.println();
        }
        for (int i = 0; i < libraries; ++i) {
            daysPassed += libraryList.get(i).signup;
            int booksShipped = (days - daysPassed) * libraryList.get(i).shipping;
            if (booksShipped > libraryList.get(i).numberOfBooks) {
                booksShipped = libraryList.get(i).numberOfBooks;
            }
            System.out.println(booksShipped);
            for (int j = 0; j < booksShipped; ++j) {
                int id = libraryList.get(i).bookList.get(j).id;
                if (!scannedBooks.get(id)) {
                    scannedBooks.set(id, true);
                    value += libraryList.get(i).bookList.get(j).value;
                }
                else if (booksShipped < libraryList.get(i).numberOfBooks){
                    ++booksShipped;
                }
            }
        }
        System.out.println(value);
    }
}

public static int maxValDays(Library library, int remainingDays){
    int days = remainingDays - library.signup;
    int sum = 0;
    for(int i = 0; i < days; i++){
        for( int k = 0; k < library.shipping; k++){
            if (library.numberOfBooks<i*library.shipping+k){
                break;
            }
            sum += library.bookList.get(i*library.shipping+k).value;
        }
    }
    return sum;
}