using System.Net.Http.Json;

namespace Smartanci_Feedback_App
{
    public partial class MainPage : ContentPage
    {
        int rating = 0;

        private static readonly HttpClient client = new HttpClient();
        public MainPage()
        {
            InitializeComponent();
            BuildRatingStars();
        }

        private void BuildRatingStars()
        {
            RatingPanel.Children.Clear();
            for (int i = 1; i <= 5; i++)
            {
                var btn = new ImageButton
                {
                    Source = ImageSource.FromFile("star_empty.png"),
                    BackgroundColor = Colors.Transparent,
                    WidthRequest = 44,
                    HeightRequest = 44,
                    Margin = new Thickness(2),
                    Opacity = 1.0,
                    CornerRadius = 8
                };
                int value = i;
                btn.Clicked += (s, e) => SetRating(value);
                RatingPanel.Children.Add(btn);
            }
            SetRating(0);
        }

        private void SetRating(int value)
        {
            rating = value;
            for (int i = 0; i < RatingPanel.Children.Count; i++)
            {
                if (RatingPanel.Children[i] is ImageButton img)
                {
                    img.Source = ImageSource.FromFile(i < rating ? "filled_star.png" : "empty_star.png");
                    img.Opacity = 1.0;
                }
            }
        }

        async void OnSendClicked(object sender, EventArgs e)
        {
            string name = EntryName.Text?.Trim() ?? string.Empty;
            string surname = EntrySurname.Text?.Trim() ?? string.Empty;
            string comment = EditorComment.Text?.Trim() ?? string.Empty;

            if (string.IsNullOrWhiteSpace(name) && string.IsNullOrWhiteSpace(comment))
            {
                await DisplayAlert("Greška", "Unesite bar ime ili komentar", "OK");
                return;
            }

            Activity.IsVisible = true;
            Activity.IsRunning = true;
            StatusLabel.IsVisible = false;


            await SendFeedbackToFormspreeAsync(name, surname, comment);     
        }

        private async Task SendFeedbackToFormspreeAsync(string name, string surname, string comment)
        {
            var formspreeUrl = "https://formspree.io/f/xrpzyjvb";

            string bodyText = $@"
                SMARTANCI - FEEDBACK PORTAL

                Korisnik: {name} {surname}
                Ocena: {rating}/5

                Komentar:
                {comment}

                Poslato putem Smartanci aplikacije
            ";

            var payload = new
            {
                name = $"{name} {surname}".Trim(),
                message = bodyText            
            };

            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));

            try
            {
                var response = await client.PostAsJsonAsync(formspreeUrl, payload);

                if (response.IsSuccessStatusCode)
                {
                    StatusLabel.TextColor = Colors.Green;
                    StatusLabel.Text = "Feedback je uspešno poslat!";
                    StatusLabel.IsVisible = true;
                    EntryName.Text = String.Empty;
                    EntrySurname.Text = String.Empty;
                    EditorComment.Text = String.Empty;
                    SetRating(0);
                }
                else
                {
                    var body = await response.Content.ReadAsStringAsync();
                    StatusLabel.TextColor = Colors.DarkRed;
                    StatusLabel.Text = $"Greška pri slanju: {body}";
                    StatusLabel.IsVisible = true;
                }
            }
            catch (Exception ex)
            {
                await DisplayAlert("Greska", ex.Message, "OK");
            }
            finally
            {
                Activity.IsRunning = false;
                Activity.IsVisible = false;
            }
        }
    }
}
