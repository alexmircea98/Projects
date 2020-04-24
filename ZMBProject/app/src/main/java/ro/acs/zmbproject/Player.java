package ro.acs.zmbproject;

public final class Player {


    private String playerName;
    private String playerId;
    private Role role;
    private boolean alive;
    private int votes;

    public Player (String playerName){
        this.playerName = playerName;
        this.playerId = "";
        alive = true;
        votes = 0;
    }

    public Player (String playerName, String playerId){
        this.playerName = playerName;
        this.playerId = playerId;
        alive = true;
        votes = 0;
    }

    public String getPlayerName() {
        return playerName;
    }

    public void setPlayerName(String playerName) {
        this.playerName = playerName;
    }

    public String getPlayerId() {
        return playerId;
    }

    public void setPlayerId(String playerId) {
        this.playerId = playerId;
    }


    public Role getRole() {
        return role;
    }

    public void setRole(Role role) {
        this.role = role;
    }

    public boolean isAlive(){
        return alive;
    }

    public void kill(){
        alive = false;
    }

    public int getVotes() {
        return votes;
    }

    public void addVote() {
        this.votes += 1;
    }

    public void resetVotes() {
        this.votes = 0;
    }
}
