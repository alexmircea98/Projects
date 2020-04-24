package ro.acs.zmbproject;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        final Button startButton1 = findViewById(R.id.button1);
        startButton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity();
            }
        });
    }

    public void startActivity(){
        Intent intent1 = new Intent(this, StartingActivity1.class);
        startActivity(intent1);
    }
}
