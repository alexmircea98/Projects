package ro.acs.zmbproject;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.CallSuper;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import com.google.android.gms.nearby.Nearby;
import com.google.android.gms.nearby.connection.ConnectionInfo;
import com.google.android.gms.nearby.connection.ConnectionLifecycleCallback;
import com.google.android.gms.nearby.connection.ConnectionResolution;
import com.google.android.gms.nearby.connection.DiscoveredEndpointInfo;
import com.google.android.gms.nearby.connection.DiscoveryOptions;
import com.google.android.gms.nearby.connection.EndpointDiscoveryCallback;
import com.google.android.gms.nearby.connection.Payload;
import com.google.android.gms.nearby.connection.PayloadCallback;
import com.google.android.gms.nearby.connection.PayloadTransferUpdate;
import com.google.android.gms.nearby.connection.Strategy;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

import java.util.ArrayList;

import static java.nio.charset.StandardCharsets.UTF_8;

public class ConnectActivity extends AppCompatActivity {



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

    private ArrayList<Player> players = new ArrayList<>();

    private ArrayList<String> nameList = new ArrayList<>();

    private Role myRole;
    private boolean amIAlive;

    private Player host;

    private TextView statusText;
    private String newPlayerName;
    private String MyName;

    // Callbacks for receiving payloads
    private final PayloadCallback payloadCallback =
            new PayloadCallback() {
                @Override
                public void onPayloadReceived(String endpointId, Payload payload) {
                    String message = new String(payload.asBytes(), UTF_8);
                    //splits the message into a string array, where first should be the message type, ex. for roles is R and followed by the recieved role
                    String[] splited = message.split("\\s+");
                    decide(splited);
                }

                @Override
                public void onPayloadTransferUpdate(String endpointId, PayloadTransferUpdate update) {
                    //do smtg else
                }
            };

    // Callbacks for finding other devices
    private final EndpointDiscoveryCallback endpointDiscoveryCallback =
            new EndpointDiscoveryCallback() {
                @Override
                public void onEndpointFound(String endpointId, DiscoveredEndpointInfo info) {
                    // An endpoint was found. We request a connection to it.
                    Log.i(TAG, "onEndpointFound: endpoint found, connecting");
                    Nearby.getConnectionsClient(ConnectActivity.this)
                            .requestConnection(MyName, endpointId, connectionLifecycleCallback)
                            .addOnSuccessListener(
                                    new OnSuccessListener<Void>() {
                                        @Override
                                        public void onSuccess(Void unused) {
                                            // We successfully requested a connection. Now both sides
                                            // must accept before the connection is established.
                                            setStatusText("endpoint found");
                                        }
                                    })
                            .addOnFailureListener(
                                    new OnFailureListener() {
                                        @Override
                                        public void onFailure(@NonNull Exception e) {
                                            // Nearby Connections failed to request the connection.
                                            setStatusText("failed request");
                                        }
                                    });
                }

                @Override
                public void onEndpointLost(String endpointId) {
                    // A previously discovered endpoint has gone away.
                    Toast.makeText(ConnectActivity.this, "Endpoint lost", Toast.LENGTH_LONG).show();
                }
            };

    // Callbacks for connections to other devices
    private final ConnectionLifecycleCallback connectionLifecycleCallback =
            new ConnectionLifecycleCallback() {
                @Override
                public void onConnectionInitiated(String endpointId, ConnectionInfo connectionInfo) {
                    Log.i(TAG, "onConnectionInitiated: accepting connection");
                    Nearby.getConnectionsClient(ConnectActivity.this).acceptConnection(endpointId, payloadCallback);
                    newPlayerName = connectionInfo.getEndpointName();

                }

                @Override
                public void onConnectionResult(String endpointId, ConnectionResolution result) {
                    if (result.getStatus().isSuccess()) {
                        Log.i(TAG, "onConnectionResult: connection successful");

                        Nearby.getConnectionsClient(ConnectActivity.this).stopDiscovery();
                        //Nearby.getConnectionsClient(HostActivity.this).stopAdvertising();


                        host = new Player(newPlayerName, endpointId);


                        setStatusText(getString(R.string.status_connected));
                    } else {
                        Log.i(TAG, "onConnectionResult: connection failed");
                    }
                }


                @Override
                public void onDisconnected(String endpointId) {
                    Log.i(TAG, "onDisconnected: disconnected from the host");

                }
            };

    public static int findPosByName(ArrayList<Player> list, String name) {
        for(int i = 0; i < list.size(); i++){
            if( list.get(i).getPlayerName().equals(name) ){
                return i;
            }
        }
        return -1;
    }

    public static Player findByName(ArrayList<Player> list, String name) {
        for(int i = 0; i < list.size(); i++){
            if( list.get(i).getPlayerName().equals(name) ){
                return list.get(i);
            }
        }
        return null;
    }

    private final void addToPlayerList(Player player){

        LinearLayout linearLayout = findViewById(R.id.playerList);

        TextView valueTV = new TextView(ConnectActivity.this);
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

    private void decide(String[] split){

        switch (split[0]){
            case "R": gotRole(Role.valueOf(split[1]));
                break;
            case "V": vote();
                break;
            case "D": dead();
                break;
            case "P": if(split[1].equals("A")){
                        players.add(new Player(split[2]));
            } else if(split[1].equals("D")){//he died
                players.get(findPosByName(players, split[2])).kill();
                if (split[2].equals(MyName)){
                    dead();
                }
            }
                break;
            default:
        }
    }

    private void gotRole(Role role) {
        myRole = role;
        amIAlive = true;
        setStatusText("Game Started");
        Button buttonCon = findViewById(R.id.discoverButton);
        buttonCon.setVisibility(View.GONE);
        showRoleCard(role);
    }

    private void showRoleCard(Role role) {
        CardSelector selector = new CardSelector(role);

        AlertDialog.Builder cardDialog = new AlertDialog.Builder(ConnectActivity.this);
//        LayoutInflater factory = LayoutInflater.from(ConnectActivity.this);
////        ImageView basicCard = (ImageView) findViewById(R.id.defaultCard);
////        basicCard.setImageResource(selector.getCardByRole(amIAlive));
//        final View view = factory.inflate(R.layout.card, null);
//        cardDialog.setView(view);
        TextView text = new TextView(this);
        text.setText(role.toString());
        cardDialog.setView(text);
        cardDialog.setNeutralButton("Close", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dlg, int sumthin) {

            }
        });

        cardDialog.show();
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

    private void vote() {
        ArrayList<String> playersToVote = new ArrayList<>();
        for(Player player : players){
            if (player.isAlive()){
                playersToVote.add(player.getPlayerName());
            }
        }
        String[] playersTV = GetStringArray(playersToVote);
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Pick a color");
        builder.setItems(playersTV, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                String nameVoted = "V " +playersTV[which];
                Nearby.getConnectionsClient(ConnectActivity.this).sendPayload(host.getPlayerId(),
                        Payload.fromBytes(nameVoted.getBytes(UTF_8)));
            }
        });
        builder.show();
    }

    private void dead() {
            amIAlive = false;
            showRoleCard(myRole);
    }


//----------------------------------------------------------//


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);

        final Button backCon = findViewById(R.id.button5);
        backCon.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        final Button connectB = findViewById(R.id.discoverButton);
        connectB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findOpponent();
            }
        });

        statusText = findViewById(R.id.statusTex);

    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onStart() {
        super.onStart();

        if (!hasPermissions(this, REQUIRED_PERMISSIONS)) {
            requestPermissions(REQUIRED_PERMISSIONS, REQUEST_CODE_REQUIRED_PERMISSIONS);
        }

    }

//    @Override
//    protected void onStop() {
//        connectionsClient.stopAllEndpoints();
//        //here was a game reset
//
//        //super.onStop();
//    }

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
        getName();
        startDiscovery();
        setStatusText(getString(R.string.status_searching));
        //findOpponentButton.setEnabled(false);
    }

    private void getName() {
        AlertDialog.Builder alert = new AlertDialog.Builder(ConnectActivity.this);

        final EditText usernameInput= new EditText(this);
        alert.setView(usernameInput);
        alert.setTitle("Pick your name");
        alert.setPositiveButton("Done", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                MyName=usernameInput.getText().toString();

                if(MyName.equals(""))
                {
                    Toast.makeText(ConnectActivity.this, "Enter a real username", Toast.LENGTH_SHORT).show();
                    alert.show();
                }
            }
        });

        alert.show();
    }

    /** Disconnects from the opponent and reset the UI. */
    public void disconnect(View view, String playerId) {
        Nearby.getConnectionsClient(this).disconnectFromEndpoint(playerId);
        //here was a game reset
    }

    /** Starts looking for other players using Nearby Connections. */
    private void startDiscovery() {
        setStatusText("Started disc");
        DiscoveryOptions discoveryOptions =
                new DiscoveryOptions.Builder().setStrategy(STRATEGY).build();
        Nearby.getConnectionsClient(this)
                .startDiscovery(this.TAG, endpointDiscoveryCallback, discoveryOptions)
                .addOnSuccessListener(
                        new OnSuccessListener<Void>() {
                            @Override
                            public void onSuccess(Void unused) {
                                // We're discovering!
                                setStatusText("We're discovering!");
                            }
                        })
                .addOnFailureListener(
                        new OnFailureListener() {
                            @Override
                            public void onFailure(@NonNull Exception e) {
                                // We're unable to start discovering.
                                setStatusText("We're unable to start discovering.");
                                startDiscovery();
                            }
                        });
    }



    /** Shows a status message to the user. */
    private void setStatusText(String text) {
        statusText.setText(text);
    }
}
