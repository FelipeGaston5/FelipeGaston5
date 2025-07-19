package com.example.minienigma;

import androidx.appcompat.app.AppCompatActivity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    EditText inputTexto;
    Spinner spinnerRotor1, spinnerRotor2, spinnerRotor3;
    TextView outputTexto;
    Button btnCodificar, btnDecodificar, btnCopiar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        inputTexto = findViewById(R.id.inputTexto);
        spinnerRotor1 = findViewById(R.id.spinnerRotor1);
        spinnerRotor2 = findViewById(R.id.spinnerRotor2);
        spinnerRotor3 = findViewById(R.id.spinnerRotor3);
        outputTexto = findViewById(R.id.outputTexto);
        btnCodificar = findViewById(R.id.btnCodificar);
        btnDecodificar = findViewById(R.id.btnDecodificar);
        btnCopiar = findViewById(R.id.btnCopiar);

        // Configurando os Spinners
        ArrayAdapter<Integer> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, getRotorValues());
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spinnerRotor1.setAdapter(adapter);
        spinnerRotor2.setAdapter(adapter);
        spinnerRotor3.setAdapter(adapter);

        btnCodificar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int r1 = (Integer) spinnerRotor1.getSelectedItem();
                int r2 = (Integer) spinnerRotor2.getSelectedItem();
                int r3 = (Integer) spinnerRotor3.getSelectedItem();

                Codificador.setRotores(r1, r2, r3);

                String texto = inputTexto.getText().toString();
                String resultado = Codificador.codificar(texto);
                outputTexto.setText(resultado);
            }
        });

        btnDecodificar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int r1 = (Integer) spinnerRotor1.getSelectedItem();
                int r2 = (Integer) spinnerRotor2.getSelectedItem();
                int r3 = (Integer) spinnerRotor3.getSelectedItem();

                Decodificador.setRotores(r1, r2, r3);

                String texto = inputTexto.getText().toString();
                String resultado = Decodificador.decodificador(texto);
                outputTexto.setText(resultado);
            }
        });

        btnCopiar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String texto = outputTexto.getText().toString();
                if (!texto.isEmpty()) {
                    ClipboardManager clipboard = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
                    ClipData clip = ClipData.newPlainText("Texto Codificado", texto);
                    clipboard.setPrimaryClip(clip);
                    Toast.makeText(MainActivity.this, "Texto copiado para a área de transferência", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "Não há texto para copiar", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    private Integer[] getRotorValues() {
        Integer[] valores = new Integer[9];
        for (int i = 0; i < 9; i++) {
            valores[i] = i + 1;
        }
        return valores;
    }
}
