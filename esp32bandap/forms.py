from django import forms

class TransportForm(forms.Form):

    initial_position = forms.ChoiceField(
        choices = [('S1', 'S1'), ('S2', 'S2'), ('S3', 'S3'), ('S4', 'S4')],
        widget = forms.Select(),
        label = "Posición inicial"
    )

    final_position = forms.ChoiceField(
        choices = [('S1', 'S1'), ('S2', 'S2'), ('S3', 'S3'), ('S4', 'S4')],
        widget = forms.Select(),
        label = "Posición final"
    )

    duration = forms.IntegerField(
        widget=forms.NumberInput(attrs={'min': 0, 'max': 9}),
        label="Duración en posición B (segundos)",
        required=False
    )
