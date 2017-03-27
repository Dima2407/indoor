package com.kit.indornavigation.ui;

import android.app.Activity;
import android.content.DialogInterface;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;

import com.kit.indornavigation.R;

/**
 * Created by kit on 9/5/16.
 */
public class DialogHelper {


    public static void showEnterNameDialog(Activity context, String title, @Nullable  String text, String hint, final EditNameListener listener) {
        View view  = LayoutInflater.from(context).inflate(R.layout.dialog_text_edit,null);
        final EditText editText = (EditText) view.findViewById(R.id.name);
        editText.setHint(hint);
        editText.setText(text);
        editText.setSelection(text!=null?text.length():0);

        AlertDialog dialog = new AlertDialog.Builder(context)
                .setTitle(title)
                .setView(view)
                .setPositiveButton("Save", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        listener.onSave(editText.getText().toString());
                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        listener.onClose();
                    }
                })
                .create();
        dialog.show();
    }

    public interface EditNameListener{
        void onSave(String text);
        void onClose();
    }


}
