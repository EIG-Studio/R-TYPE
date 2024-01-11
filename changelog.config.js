module.exports = {
    disableEmoji: true,
    format: '{type}{scope} {emoji}{subject}',
    list: ['[ADD]', '[FIX]', '[RM]', '[EDIT]'],
    maxMessageLength: 64,
    minMessageLength: 3,
    questions: ['type', 'scope', 'subject', 'body', 'breaking', 'issues', 'lerna'],
    scopes: [],
    types: {
        "[ADD]": {
            description: 'Use this action when adding new features, files, or functionality to the codebase.',
            value: '[ADD]'
        },
        "[FIX]": {
            description: 'Use this action when addressing and resolving bugs or issues.',
            value: '[FIX]'
        },
        "[RM]": {
            description: 'Use this action when removing or deprecating existing features, files, or functionality.',
            value: '[RM]'
        },
        "[EDIT]": {
            description: 'Use this action when making minor modifications or updates that don\'t fit under the other categories.',
            value: '[EDIT]'
        },
        messages: {
            type: 'Select the type of change that you\'re committing:',
            customScope: 'Select the scope this component affects:',
            subject: 'Write a short, imperative mood description of the change:\n',
            body: 'Provide a longer description of the change:\n ',
            breaking: 'List any breaking changes:\n',
            footer: 'Issues this commit closes, e.g #123:',
            confirmCommit: 'The packages that this commit has affected\n',
        },
    }
};
