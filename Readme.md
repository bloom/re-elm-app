# This project isn't as good as this other project!

https://github.com/jaredramirez/reason-elm

👆 use that one instead!


# re-elm-app

```
yarn add re-elm-app
```

Then add

```
  "bs-dependencies": ["re-elm-app"]
```

to your bsconfig.json.

Then you can use it like this (assuming you have some webpack setup that can import Elm files like [elm-webpack-loader](https://github.com/elm-community/elm-webpack-loader)):

```reason
[@bs.module "./Main.elm"] external main : ElmApp.unmounted = "Main";

/* These are just some example flags. It's just a json value */
let flags =
 Js.Dict.fromList([
   ("images", images),
   ("publicUrl", publicUrl),
   ("user", userJson)
 ]);

/* Mount the app, and then you can subscribe to its ports. Here the callbacks specified below are just functions (not shown in this example) which take Js.Json.t and return unit. */
ElmApp.mount("#root", flags, main)
|> ElmApp.subscribeToPort("log_", onElmLog)
|> ElmApp.subscribeToPort("toJS", onElmMsg)
```
