using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace Correlator.Pages;

public class IndexModel : PageModel
{
    private readonly ILogger<IndexModel> _logger;

    public IndexModel(ILogger<IndexModel> logger)
    {
        _logger = logger;
    }

    public void OnGet()
    {

    }

    public string Message { get; set; } = "Request Initiation Waiting...";

    public async void OnPostCallAPI()
    {
        string body = new StreamReader(this.Request.Body).ReadToEndAsync().Result;
        Result result = Newtonsoft.Json.JsonConvert.DeserializeObject<Result>(body);
    }
}
