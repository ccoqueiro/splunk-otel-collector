# Changelog

## Unreleased

## ansible-v0.6.0

### 🧰 Bug fixes 🧰

- Fix `SPLUNK_TRACE_URL` and `SPLUNK_HEC_URL` env vars (#1290)

## ansible-v0.5.0

### 💡 Enhancements 💡

- Bump default td-agent version to 4.3.0 (#1218)

### 🧰 Bug fixes 🧰

- Add `ansible.windows` as a galaxy dependency (#1229)

## ansible-v0.4.0

### 💡 Enhancements 💡

- Add an option to provide a custom configuration that will be merged into the
  default one using `splunk_config_override` var (#950)

## ansible-v0.3.0

### 🛑 Breaking changes 🛑

- Rename `agent_bundle_dir` parameter to `splunk_bundle_dir` (#810)

### 💡 Enhancements 💡

- Add Windows support (#646, #797)
- Add SUSE support (collector only) (#748)
- Use `template` instead of `copy` to manage the configuration file (#770)

## ansible-v0.2.0

- Add proxy support for otel collector service runtime level (#699)
- Drop `apt_key` deprecated module in favor of existing `get_url` task (#698)

## ansible-v0.1.3

- Add meta/runtime.yml (#690)

## ansible-v0.1.2

- Install libcap on RHEL platforms (#678)

## ansible-v0.1.1

### 🧰 Bug fixes 🧰

- Remove redundant import_tasks (#420)
- Fill fully qualified task names where missed (#420)
- Fix conditions to avoid warning (#420)

## ansible-v0.1.0

Initial version of `signalfx.splunk_otel_collector` Ansible Collection with 
Linux support.
