using Octokit;
using System.Diagnostics;
using System.Reflection;

namespace Common
{
    public class UpdateChecker
    {
        private static UpdateChecker? _instance;
        public Assembly? Assembly { get; set; }

        public delegate void UpdateCheckerDelegate(Version localVersion, Version remoteVersion, Uri downloadLink);
        public UpdateCheckerDelegate? UpdateCheckCallback;

        private UpdateChecker() { }

        public static UpdateChecker Get()
        {
            _instance ??= new();

            return _instance;
        }

        public void Check(string name)
        {
            //Github
            GitHubClient client = new(new ProductHeaderValue("SomeName"));
            IReadOnlyList<Release> releases = client.Repository.Release.GetAll("gttrcr", name).Result;
            Release latestRemove = releases.First();
            Version removeVersion = new(latestRemove.TagName);

            //local
            FileVersionInfo fvi = FileVersionInfo.GetVersionInfo(Assembly.Location);
            Version localVersion = new(fvi.ProductVersion);

            //comparison
            int versionComparison = localVersion.CompareTo(removeVersion);
            if (versionComparison < 0)
                //The version on GitHub is more up to date than this local release.
                UpdateCheckCallback?.Invoke(localVersion, removeVersion, new Uri(latestRemove.HtmlUrl));
            else if (versionComparison > 0)
            {
                //This local version is greater than the release version on GitHub.
            }
            else
            {
                //This local Version and the Version on GitHub are equal.
            }
        }
    }
}