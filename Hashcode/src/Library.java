public class Library {
    int numberOfBooks;
    int signup;
    int shipping;
    ArrayList<Book> bookList;
    int value;

    public Library(int numberOfBooks, int signup, int shipping) {
        this.numberOfBooks = numberOfBooks;
        this.signup = signup;
        this.shipping = shipping;
        bookList = new ArrayList<Book>();
    }
}