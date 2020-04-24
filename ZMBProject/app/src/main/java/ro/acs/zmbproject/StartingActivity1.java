package ro.acs.zmbproject;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class StartingActivity1 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_starting1);

        final Button hostB = findViewById(R.id.button);
        hostB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                goHost();
            }
        });

        final Button connectB = findViewById(R.id.button2);
        connectB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                goConnect();
            }
        });

        final Button backB = findViewById(R.id.button3);
        backB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
    }

    public void goHost() {
        Intent intentHost = new Intent(this, HostActivity.class);
        startActivity(intentHost);
    }

    public void goConnect() {
        Intent intentConnect = new Intent(this, ConnectActivity.class);
        startActivity(intentConnect);
    }


}
