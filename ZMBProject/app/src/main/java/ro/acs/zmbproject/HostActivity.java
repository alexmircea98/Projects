package ro.acs.zmbproject;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.util.Pair;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.NumberPicker;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.CallSuper;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import com.google.android.gms.nearby.Nearby;
import com.google.android.gms.nearby.connection.AdvertisingOptions;
import com.google.android.gms.nearby.connection.ConnectionInfo;
import com.google.android.gms.nearby.connection.ConnectionLifecycleCallback;
import com.google.android.gms.nearby.connection.ConnectionResolution;
import com.google.android.gms.nearby.connection.Payload;
import com.google.android.gms.nearby.connection.PayloadCallback;
import com.google.android.gms.nearby.connection.PayloadTransferUpdate;
import com.google.android.gms.nearby.connection.Strategy;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

import java.util.ArrayList;

import static java.nio.charset.StandardCharsets.UTF_8;


public class HostActivity extends AppCompatActivity {


    private static final String TAG = "198234298792873497987";

    private static final String[] REQUIRED_PERMISSIONS =
            new String[] {
                    Manifest.permission.BLUETOOTH,
                    Manifest.permission.BLUETOOTH_ADMIN,
                    Manifest.permission.ACCESS_WIFI_STATE,
                    Manifest.permission.CHANGE_WIFI_STATE,
                    Manifest.permission.ACCESS_COARSE_LOCATION,
            };

    private static final int REQUEST_CODE_REQUIRED_PERMISSIONS = 1;

    private static final Strategy STRATEGY = Strategy.P2P_CLUSTER;

    // Our randomly generated name
    private final String codeName = CodenameGenerator.generate();

    private ArrayList<Player> players = new ArrayList<>();
    private int[] selection = new int[Role.values().length];

    private TextView statusText;
    private String newPlayerName;
    private int playerCount;
    private int votesCount;



    // Callbacks for receiving payloads
    private final PayloadCallback payloadCallback =
            new PayloadCallback() {
                @Override
                public void onPayloadReceived(String endpointId, Payload payload) {

                    String message = new String(payload.asBytes(), UTF_8);
                    //splits the message into a string array, where first should be the message type, ex. for roles is R and followed by the recieved role
                    String[] splited = message.split("\\s+");
                    switch (splited[0]){
                        case "V": {
                            findByName(players, splited[1]).addVote();
                            votesCount++;
                        }
                            break;
                        default:
                    }


                }

                @Override
                public void onPayloadTransferUpdate(String endpointId, PayloadTransferUpdate update) {
                    //do smtg else
                }
            };




    // Callbacks for connections to other devices
    private final ConnectionLifecycleCallback connectionLifecycleCallback =
            new ConnectionLifecycleCallback() {
                @Override
                public void onConnectionInitiated(String endpointId, ConnectionInfo connectionInfo) {
                    Log.i(TAG, "onConnectionInitiated: accepting connection");
                    Nearby.getConnectionsClient(HostActivity.this).acceptConnection(endpointId, payloadCallback);
                    newPlayerName = connectionInfo.getEndpointName();

                }

                @Override
                public void onConnectionResult(String endpointId, ConnectionResolution result) {
                    if (result.getStatus().isSuccess()) {
                        Log.i(TAG, "onConnectionResult: connection successful");

                        //connectionsClient.stopDiscovery();
                        //Nearby.getConnectionsClient(HostActivity.this).stopAdvertising();


                        Player temp = new Player(newPlayerName, endpointId);
                        players.add(temp);
                        addToPlayerList(temp);
                        playerCount++;

                        setStatusText(getString(R.string.status_connected));

                        //setButtonState(true);
                    } else {
                        Log.i(TAG, "onConnectionResult: connection failed");
                    }
                }


                @Override
                public void onDisconnected(String endpointId) {
                    Log.i(TAG, "onDisconnected: disconnected from the opponent");
                    deletePlayerList(findById(players, endpointId));
                    players.remove(findById(players, endpointId));
                    playerCount--;

                }
            };

    public static Player findById(ArrayList<Player> list, String id) {
        for(int i = 0; i < list.size(); i++){
            if( list.get(i).getPlayerId().equals(id) ){
                return list.get(i);
            }
        }
        return null;
    }

    public static Player findByName(ArrayList<Player> list, String id) {
        for(int i = 0; i < list.size(); i++){
            if( list.get(i).getPlayerName().equals(id) ){
                return list.get(i);
            }
        }
        return null;
    }

    private final void addToPlayerList(Player player){

        LinearLayout linearLayout = findViewById(R.id.playerList);

        TextView valueTV = new TextView(HostActivity.this);
        valueTV.setText(player.getPlayerName());
        valueTV.setId(players.lastIndexOf(player));
        valueTV.setLayoutParams(new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT));

        linearLayout.addView(valueTV);
    }

    private final void deletePlayerList(Player player){
        LinearLayout linearLayout = findViewById(R.id.playerList);
        linearLayout.removeView(findViewById(players.lastIndexOf(player)));
    }

    private final void modPlayerRole(Player player, Role role, String status){
        LinearLayout linearLayout = findViewById(R.id.playerList);
        TextView stat = linearLayout.findViewById(players.lastIndexOf(player));
        stat.setText(player.getPlayerName() + " " + role.toString() + " " + status);
    }




                  //----------------------------------------------------------//





    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_host);


        final Button backHost = findViewById(R.id.button4);
        backHost.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        final Button connectB = findViewById(R.id.advertButton);
        connectB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findOpponent();
            }
        });

        final Button startB = findViewById(R.id.button6);
        startB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                drawRoles();
                sendListToPlayers();
                findViewById(R.id.button6).setEnabled(false);
                findViewById(R.id.advertButton).setEnabled(false);
                findViewById(R.id.optB).setEnabled(false);
            }
        });



        final Button optionsB = findViewById(R.id.optB);
        optionsB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                numberPick();
            }
        });

        final Button killB = findViewById(R.id.killButton);
        killB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                killPlayer();
            }
        });

        final Button startVoteB = findViewById(R.id.startVote);
        startVoteB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startVote();
            }
        });

        statusText = findViewById(R.id.statusTex2);

        playerCount = 0;


    }

    private void startVote() {
        votesCount = 0;
        int stillAlive = 0;
        ArrayList<Player> playersToVote = new ArrayList<>();
        for(Player player : players){
            if (player.isAlive()){
                stillAlive++;
                playersToVote.add(player);
            }
        }
        //send signal to vote
        for(Player voter : playersToVote){
            Nearby.getConnectionsClient(HostActivity.this).sendPayload(voter.getPlayerId(),
                    Payload.fromBytes("V".getBytes(UTF_8)));
        }
        //wait for votes
        long t= System.currentTimeMillis();
        long end = t+15000;
        while(System.currentTimeMillis() < end) {
            if (votesCount == stillAlive){
                break;
            }
        }
        //decide winner
        votesCount = 0;
        Player mostVoted = new Player("dummy");

        //count the votes and find most voted
        for(Player player : players){
            if (player.getVotes() > votesCount){
                mostVoted = player;
                votesCount = player.getVotes();
            } else if(player.getVotes() == votesCount && votesCount != 0){
                mostVoted = null; //in case there is no unique max, there is a draw
            }
        }
        if (mostVoted != null){
            kill(mostVoted);
        }

        //clear the votes
        for(Player player : players){
            player.resetVotes();
        }

    }

    // Function to convert ArrayList<String> to String[]
    public static String[] GetStringArray(ArrayList<String> arr)
    {

        // declaration and initialise String Array
        String str[] = new String[arr.size()];

        // ArrayList to Array Conversion
        for (int j = 0; j < arr.size(); j++) {

            // Assign each value to String array
            str[j] = arr.get(j);
        }

        return str;
    }

    private void killPlayer() {

        ArrayList<String> playersToVote = new ArrayList<>();
        for(Player player : players){
            if (player.isAlive()){
                playersToVote.add(player.getPlayerName());
            }
        }
        String[] stillAlive = GetStringArray(playersToVote);

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Pick a color");
        builder.setItems(stillAlive, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                kill(findByName(players, stillAlive[which]));
            }
        });
        builder.show();
    }

    private void kill(Player player) {
        player.kill();
        modPlayerRole(player, player.getRole(), "dead");
        sendUpdateToPlayers(player, "D");


    }

    private void sendListToPlayers() {
        for(Player playerToSendto :players){
            for(Player playername: players){
                Nearby.getConnectionsClient(this).sendPayload(playerToSendto.getPlayerId(),
                        Payload.fromBytes(("P A " + playername.getPlayerName()).getBytes(UTF_8)));
            }

        }
    }

    private void sendUpdateToPlayers( Player player, String action ) { //action should be D dead, A alive, add others...
        for(Player playerToSendto :players){
                Nearby.getConnectionsClient(this).sendPayload(playerToSendto.getPlayerId(),
                        Payload.fromBytes(("P " + action + " " + player.getPlayerName()).getBytes(UTF_8)));

        }
    }


    private void numberPick(){
        ArrayList<Pair<TextView,EditText>> lines = new ArrayList<>(Role.values().length);
        //Create LinearLayout Dynamically
        LinearLayout layout = new LinearLayout(this);

        //Setup Layout Attributes
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layout.setLayoutParams(params);
        layout.setOrientation(LinearLayout.VERTICAL);

        for(int i = 0; i < Role.values().length; i++){

            lines.add(new Pair(new TextView(this), new EditText(this)));
            lines.get(i).first.setText(Role.values()[i].toString()+ ":");

            //Create a TextView to add to layout
            lines.get(i).second.setText(String.valueOf(selection[i]));


            //Add Views to the layout
            layout.addView(lines.get(i).first);
            layout.addView(lines.get(i).second);
        }



        //Create AlertDialog Builder
        AlertDialog.Builder builder = new AlertDialog.Builder(this);

        //Give the Dialog a Title
        builder.setTitle("Results");

        builder.setView(layout);

        //Add Dialog button that will just close the Dialog
        builder.setNeutralButton("Done", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {

                int sum = 0;
                for(Pair<TextView,EditText> pair : lines){
                    sum += Integer.parseInt(pair.second.getText().toString());
                }
                if (sum > playerCount){
                    Toast.makeText(getApplicationContext(),"Too many roles",Toast.LENGTH_LONG).show();
                } else if(sum < playerCount){
                    Toast.makeText(getApplicationContext(),"Too little roles, add more",Toast.LENGTH_LONG).show();
                } else {
                    for(int k = 0; k < lines.size(); k++){
                        selection[k] = Integer.parseInt(lines.get(k).second.getText().toString());
                    }
                    dialog.dismiss();
                }
            }
        });

        //Show the custom AlertDialog
        AlertDialog alert = builder.create();
        alert.show();
    }

    private void drawRoles() {
        ArrayList<Role> roles = new ArrayList<>();
        int sum = 0;
        //fill roles from selection, if selection is empty or not filled for all players show err msg
        for(int k : selection){
            sum += k;
        }
        if (sum == playerCount) {
            for (int n = 0; n < Role.values().length; n++) {
                for (int j = selection[n]; j > 0; j--) {
                    roles.add(Role.values()[n]);
                }
            }
            // else shuffle roles and send em
            for (int i = 0; i < players.size(); i++) {
                draw(players.get(i), roles.get(i));
            }
        } else {
            Toast.makeText(getApplicationContext(),"Roles are not equal to players",Toast.LENGTH_LONG).show();
        }
    }

    private void draw(Player player, Role role){
        String message = "R " + role.toString();
        player.setRole(role);
        modPlayerRole(player, role, "alive");
        Nearby.getConnectionsClient(this).sendPayload(player.getPlayerId(),
                Payload.fromBytes(message.getBytes(UTF_8)));
        Log.i("DRAWcards", "Sent role " +role.toString()+ " to player " + player.getPlayerName());


    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onStart() {
        super.onStart();

        if (!hasPermissions(this, REQUIRED_PERMISSIONS)) {
            requestPermissions(REQUIRED_PERMISSIONS, REQUEST_CODE_REQUIRED_PERMISSIONS);
        }

    }

    @Override
    protected void onStop() {
        Nearby.getConnectionsClient(this).stopAllEndpoints();
        findViewById(R.id.button6).setEnabled(true);
        findViewById(R.id.advertButton).setEnabled(true);
        findViewById(R.id.optB).setEnabled(true);

        super.onStop();
    }



    /** Returns true if the app was granted all the permissions. Otherwise, returns false. */
    private static boolean hasPermissions(Context context, String... permissions) {
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(context, permission)
                    != PackageManager.PERMISSION_GRANTED) {
                return false;
            }
        }
        return true;
    }

    /** Handles user acceptance (or denial) of our permission request. */
    @CallSuper
    @Override
    public void onRequestPermissionsResult(
            int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode != REQUEST_CODE_REQUIRED_PERMISSIONS) {
            return;
        }

        for (int grantResult : grantResults) {
            if (grantResult == PackageManager.PERMISSION_DENIED) {
                Toast.makeText(this, R.string.error_missing_permissions, Toast.LENGTH_LONG).show();
                finish();
                return;
            }
        }
        recreate();
    }

    /** Finds an opponent to play the game with using Nearby Connections. */
    public void findOpponent() {
        startAdvertising();
        setStatusText(getString(R.string.status_searching));
        //findOpponentButton.setEnabled(false);
    }

    /** Disconnects from the opponent and reset the UI. */
    public void disconnect(View view, String playerId) {
        Nearby.getConnectionsClient(this).disconnectFromEndpoint(playerId);
        //here was a game reset
    }


    /** Broadcasts our presence using Nearby Connections so other players can find us. */
    private void startAdvertising() {
        setStatusText("Started ad");
        AdvertisingOptions advertisingOptions =
                new AdvertisingOptions.Builder().setStrategy(STRATEGY).build();
        Nearby.getConnectionsClient(this)
                .startAdvertising(
                        codeName, this.TAG, connectionLifecycleCallback, advertisingOptions)
                .addOnSuccessListener(
                        new OnSuccessListener<Void>() {
                            @Override
                            public void onSuccess(Void unused) {
                                // We're advertising!
                                setStatusText("We're discovering!");

                            }
                        })
                .addOnFailureListener(
                        new OnFailureListener() {
                            @Override
                            public void onFailure(@NonNull Exception e) {
                                // We were unable to start advertising.
                                setStatusText("We're unable to start discovering.");
                                startAdvertising();
                            }
                        });
    }

    /** Shows a status message to the user. */
    private void setStatusText(String text) {
        statusText.setText(text);
    }

    public int getPlayerCount() {
        return playerCount;
    }

    public void setPlayerCount(int playerCount) {
        this.playerCount = playerCount;
    }

}
