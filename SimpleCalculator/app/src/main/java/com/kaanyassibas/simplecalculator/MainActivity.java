package com.kaanyassibas.simplecalculator;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity
{
    EditText number1;
    EditText number2;
    TextView result;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        number1 = findViewById(R.id.number1);
        number2 = findViewById(R.id.number2);
        result = findViewById(R.id.result);
    }



    public void sum(View view)
    {
        if (number1.getText().toString().isEmpty() || number2.getText().toString().isEmpty())
        {
            result.setText("Enter the number(s).");
            return;
        }

            double no1 = Double.parseDouble(number1.getText().toString());
            double no2 = Double.parseDouble(number2.getText().toString());

            double sumResult = no1 + no2;

            result.setText("Result: " + sumResult);
    }

    public void sub(View view)
    {
        if (number1.getText().toString().isEmpty() || number2.getText().toString().isEmpty())
        {
            result.setText("Enter the number(s).");
            return;
        }

            double no1 = Double.parseDouble(number1.getText().toString());
            double no2 = Double.parseDouble(number2.getText().toString());

            double subResult = no1 - no2;

            result.setText("Result: " + String.format("%.2f", subResult));
    }

    public void mul(View view)
    {
        if (number1.getText().toString().isEmpty() || number2.getText().toString().isEmpty())
        {
            result.setText("Enter the number(s).");
            return;
        }

            double no1 = Double.parseDouble(number1.getText().toString());
            double no2 = Double.parseDouble(number2.getText().toString());

            double mulResult = no1 * no2;

            result.setText("Result: " + String.format("%.2f", mulResult));
    }

    public void div(View view)
    {
        String no1String = number1.getText().toString();
        String no2String = number2.getText().toString();

        if (no1String.isEmpty() || no2String.isEmpty())
        {
            result.setText("Enter the number(s).");
            return;
        }

        double no1 = Double.parseDouble(no1String);
        double no2 = Double.parseDouble(no2String);

        if (no2 == 0)
        {
            result.setText("Can not divide by 0!");
            return;
        }

            double divResult = no1 / no2;

            result.setText("Result: " + String.format("%.2f", divResult));
    }
}