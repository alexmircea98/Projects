package ro.acs.zmbproject;

enum Role {
    ASSASSIN,
    CIVILIAN,
    DETECTIVE,
    HACKER,
    DOCTOR,
    VETERAN
}

enum Time {
    Day,
    Night
}

public class CardSelector {
    Role role;

    // Constructor
    public CardSelector(Role role) {
        this.role = role;
    }

    // Prints a line about Day using switch
    public int getCardByRole(boolean alive) {

        switch (role) {
            case ASSASSIN:
                if (alive) return R.drawable.bg;
                return R.drawable.bg;

            case CIVILIAN:
                if (alive) return R.drawable.bg;
                return R.drawable.bg;

            case DETECTIVE:
                if (alive) return R.drawable.bg;
                return R.drawable.bg;

            case HACKER:
                if (alive) return R.drawable.bg;
                return R.drawable.bg;

            case DOCTOR:
                if (alive) return R.drawable.bg;
                return R.drawable.bg;

            case VETERAN:
                if (alive) return R.drawable.bg;
                return R.drawable.bg;

            default:
                return R.drawable.bg;
        }
    }
}