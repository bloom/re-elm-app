type t;

type flags = Js.Dict.t(Js.Json.t);

type unmounted = {. "embed": [@bs.meth] ((Dom.node, flags) => t)};

type listener = Js.Json.t => unit;

type portMsg = {. "tag": string, "payload": Js.Json.t};

exception ErrorDecodingPortMsg(string, string);

exception MountPointNotFound(string);

[@bs.scope "document"] [@bs.val] external querySelector : string => Js.nullable(Dom.node) = "";

/* Finds the DOM node with the provided selector. If the node can't be found, a MountPointNotFound
   exception is raised. */
let mount = (selector: string, flags: flags, unmountedApp: unmounted) : t =>
  switch (Js.toOption(querySelector(selector))) {
  | Some(n) => unmountedApp##embed(n, flags)
  | None => raise(MountPointNotFound(selector))
  };

let decodePortMsg = (json: Js.Json.t) : Js.Result.t(portMsg, string) =>
  try (
    Js.Result.Ok(
      Json.Decode.(
        {"tag": json |> field("tag", string), "payload": json |> field("payload", (a) => a)}
      )
    )
  ) {
  | Json.Decode.DecodeError(e) => Js.Result.Error(e)
  };

let subscribeToPort: (string, listener, t) => t = [%bs.raw
  {|(portName, cb, app) => {
      app.ports[portName].subscribe(cb);
      return app;
    }
    |}
];
